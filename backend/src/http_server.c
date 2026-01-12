#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <ctype.h>
#include "csv.h"
#include "array_ops.h"
#include "sort.h"

#define PORT 8080
#define BUFFER_SIZE 16384
#define MAX_CLIENTS 10
#define MAX_FILE_SIZE (50 * 1024 * 1024)
#define UPLOAD_DIR "images"

Image* global_images = NULL;
int global_count = 0;
pthread_mutex_t data_lock = PTHREAD_MUTEX_INITIALIZER;

// Ensure upload directory exists
void ensure_upload_dir() {
    mkdir(UPLOAD_DIR, 0755);
}

// JSON response helpers
void send_json_response(int client_fd, int status, const char* json_body) {
    char response[16384];
    snprintf(response, sizeof(response),
        "HTTP/1.1 %d OK\r\n"
        "Content-Type: application/json\r\n"
        "Access-Control-Allow-Origin: *\r\n"
        "Access-Control-Allow-Methods: GET, POST, DELETE, OPTIONS\r\n"
        "Access-Control-Allow-Headers: Content-Type, multipart/form-data\r\n"
        "Content-Length: %lu\r\n"
        "Connection: close\r\n"
        "\r\n"
        "%s",
        status, strlen(json_body), json_body);
    send(client_fd, response, strlen(response), 0);
}

void send_file_response(int client_fd, const char* filepath) {
    FILE* fp = fopen(filepath, "rb");
    if (!fp) {
        send_error(client_fd, "File not found");
        return;
    }

    fseek(fp, 0, SEEK_END);
    long filesize = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    char header[512];
    snprintf(header, sizeof(header),
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: image/jpeg\r\n"
        "Content-Length: %ld\r\n"
        "Access-Control-Allow-Origin: *\r\n"
        "Connection: close\r\n"
        "\r\n",
        filesize);

    send(client_fd, header, strlen(header), 0);

    char buffer[4096];
    int bytes;
    while ((bytes = fread(buffer, 1, sizeof(buffer), fp)) > 0) {
        send(client_fd, buffer, bytes, 0);
    }

    fclose(fp);
}

void send_error(int client_fd, const char* message) {
    char json[1024];
    snprintf(json, sizeof(json), "{\"error\":\"%s\"}", message);
    send_json_response(client_fd, 400, json);
}

// API Endpoints

void handle_get_images(int client_fd) {
    pthread_mutex_lock(&data_lock);
    
    char response[16384] = "{\"images\":[";
    
    for (int i = 0; i < global_count; i++) {
        char img_json[512];
        snprintf(img_json, sizeof(img_json),
            "%s{\"id\":%d,\"filename\":\"%s\",\"width\":%d,\"height\":%d,\"size_kb\":%.2f,\"bit_depth\":%d}",
            i > 0 ? "," : "",
            global_images[i].id,
            global_images[i].filename,
            global_images[i].width,
            global_images[i].height,
            global_images[i].size_kb,
            global_images[i].bit_depth
        );
        strcat(response, img_json);
    }
    strcat(response, "]}");
    
    pthread_mutex_unlock(&data_lock);
    send_json_response(client_fd, 200, response);
}

void handle_add_image(int client_fd, const char* body) {
    int id, width, height, bit_depth;
    char filename[100];
    float size_kb;
    
    // Parse JSON: {"id":1,"filename":"test.jpg","width":800,"height":600,"size_kb":150.5,"bit_depth":24}
    if (sscanf(body, "{\"id\":%d,\"filename\":\"%99[^\"]\"", &id, filename) < 2) {
        send_error(client_fd, "Invalid JSON format");
        return;
    }
    
    sscanf(body, "\"width\":%d", &width);
    sscanf(body, "\"height\":%d", &height);
    sscanf(body, "\"size_kb\":%f", &size_kb);
    sscanf(body, "\"bit_depth\":%d", &bit_depth);
    
    pthread_mutex_lock(&data_lock);
    global_images = realloc(global_images, (global_count + 1) * sizeof(Image));
    
    global_images[global_count].id = id;
    strcpy(global_images[global_count].filename, filename);
    global_images[global_count].width = width;
    global_images[global_count].height = height;
    global_images[global_count].size_kb = size_kb;
    global_images[global_count].bit_depth = bit_depth;
    
    global_count++;
    
    // Save to CSV
    saveCSV("data/images.csv", global_images, global_count);
    
    pthread_mutex_unlock(&data_lock);
    
    char response[256];
    snprintf(response, sizeof(response), "{\"success\":true,\"message\":\"Image added\",\"id\":%d}", id);
    send_json_response(client_fd, 200, response);
}

// Custom function to find string in buffer, needed for multipart parsing
char* strnstr(const char* haystack, const char* needle, size_t len) {
    if (!needle || !*needle) return (char*)haystack;
    size_t needle_len = strlen(needle);
    if (needle_len == 0) return (char*)haystack;

    for (size_t i = 0; i <= len - needle_len; i++) {
        if (haystack[i] == *needle && memcmp(haystack + i, needle, needle_len) == 0) {
            return (char*)(haystack + i);
        }
    }
    return NULL;
}

// Parse multipart form data and extract file and fields
int parse_multipart_upload(const char* buffer, ssize_t bytes, int* id, int* width, int* height, int* bit_depth) {
    // Get boundary
    char* boundary_start = strnstr(buffer, "boundary=", bytes);
    if (!boundary_start) return 0;
    boundary_start += 9;
    char* boundary_end = strnstr(boundary_start, "\r\n", bytes - (boundary_start - buffer));
    if (!boundary_end) return 0;

    char boundary[256];
    snprintf(boundary, sizeof(boundary), "--%.*s", (int)(boundary_end - boundary_start), boundary_start);

    // Helper to find a form field and get its value
    auto char* find_field_value(const char* field_name, const char* buf, size_t len);
    char* find_field_value(const char* field_name, const char* buf, size_t len) {
        char search_str[256];
        snprintf(search_str, sizeof(search_str), "Content-Disposition: form-data; name=\"%s\"\r\n\r\n", field_name);
        char* field_pos = strnstr(buf, search_str, len);
        if (!field_pos) return NULL;
        
        field_pos += strlen(search_str);
        char* field_end = strnstr(field_pos, "\r\n", len - (field_pos - buf));
        if (!field_end) return NULL;

        static char value[256];
        snprintf(value, sizeof(value), "%.*s", (int)(field_end - field_pos), field_pos);
        return value;
    }

    // Extract fields
    char* id_str = find_field_value("id", buffer, bytes);
    if (id_str) *id = atoi(id_str); else return 0;

    char* width_str = find_field_value("width", buffer, bytes);
    if (width_str) *width = atoi(width_str); else return 0;

    char* height_str = find_field_value("height", buffer, bytes);
    if (height_str) *height = atoi(height_str); else return 0;

    char* bit_depth_str = find_field_value("bit_depth", buffer, bytes);
    if (bit_depth_str) *bit_depth = atoi(bit_depth_str); else *bit_depth = 24;

    // Find file content
    char* file_header_start = strnstr(buffer, "Content-Disposition: form-data; name=\"file\"", bytes);
    if (!file_header_start) return 0;

    char* file_body_start = strnstr(file_header_start, "\r\n\r\n", bytes - (file_header_start - buffer));
    if (!file_body_start) return 0;
    file_body_start += 4;

    char* file_body_end = strnstr(file_body_start, boundary, bytes - (file_body_start - buffer));
    if (!file_body_end) return 0;
    // Adjust for final CRLF before boundary
    if (file_body_end > buffer + 2 && file_body_end[-2] == '\r' && file_body_end[-1] == '\n') {
        file_body_end -= 2;
    }


    ssize_t file_size = file_body_end - file_body_start;
    if (file_size <= 0 || file_size > MAX_FILE_SIZE) return 0;

    // Save file
    ensure_upload_dir();
    char filepath[256];
    snprintf(filepath, sizeof(filepath), "%s/%d.jpg", UPLOAD_DIR, *id);

    FILE* fp = fopen(filepath, "wb");
    if (!fp) return 0;

    fwrite(file_body_start, 1, file_size, fp);
    fclose(fp);

    // Add to database
    pthread_mutex_lock(&data_lock);
    global_images = realloc(global_images, (global_count + 1) * sizeof(Image));

    global_images[global_count].id = *id;
    snprintf(global_images[global_count].filename, sizeof(global_images[global_count].filename), "%d.jpg", *id);
    global_images[global_count].width = *width;
    global_images[global_count].height = *height;
    global_images[global_count].size_kb = (float)file_size / 1024.0;
    global_images[global_count].bit_depth = *bit_depth;

    global_count++;

    saveCSV("data/images.csv", global_images, global_count);
    pthread_mutex_unlock(&data_lock);

    return 1;
}

void handle_upload_image(int client_fd, const char* body, ssize_t body_size) {
    int id, width, height, bit_depth;

    if (parse_multipart_upload(body, body_size, &id, &width, &height, &bit_depth)) {
        char response[256];
        snprintf(response, sizeof(response),
            "{\"success\":true,\"message\":\"Image uploaded\",\"id\":%d}", id);
        send_json_response(client_fd, 201, response); // 201 Created
    } else {
        send_error(client_fd, "Failed to parse upload data or save file");
    }
}

void handle_get_image(int client_fd, const char* query) {
    int id;
    if (sscanf(query, "%d", &id) < 1) {
        send_error(client_fd, "Invalid ID");
        return;
    }

    pthread_mutex_lock(&data_lock);
    
    for (int i = 0; i < global_count; i++) {
        if (global_images[i].id == id) {
            char filepath[256];
            snprintf(filepath, sizeof(filepath), "%s/%d.jpg", UPLOAD_DIR, id);
            pthread_mutex_unlock(&data_lock);
            send_file_response(client_fd, filepath);
            return;
        }
    }
    
    pthread_mutex_unlock(&data_lock);
    send_error(client_fd, "Image not found");
}

void handle_download_image(int client_fd, const char* query) {
    int id;
    if (sscanf(query, "%d", &id) < 1) {
        send_error(client_fd, "Invalid ID");
        return;
    }

    pthread_mutex_lock(&data_lock);
    
    for (int i = 0; i < global_count; i++) {
        if (global_images[i].id == id) {
            char filepath[256];
            snprintf(filepath, sizeof(filepath), "%s/%d.jpg", UPLOAD_DIR, id);
            
            char response[512];
            snprintf(response, sizeof(response),
                "HTTP/1.1 200 OK\r\n"
                "Content-Type: image/jpeg\r\n"
                "Content-Disposition: attachment; filename=\"%s\"\r\n"
                "Access-Control-Allow-Origin: *\r\n"
                "Connection: close\r\n"
                "\r\n",
                global_images[i].filename);
            
            send(client_fd, response, strlen(response), 0);
            
            FILE* fp = fopen(filepath, "rb");
            if (fp) {
                char buffer[4096];
                int bytes;
                while ((bytes = fread(buffer, 1, sizeof(buffer), fp)) > 0) {
                    send(client_fd, buffer, bytes, 0);
                }
                fclose(fp);
            }
            
            pthread_mutex_unlock(&data_lock);
            return;
        }
    }
    
    pthread_mutex_unlock(&data_lock);
    send_error(client_fd, "Image not found");
}

void handle_search_image(int client_fd, const char* query) {
    int id;
    sscanf(query, "id=%d", &id);
    
    pthread_mutex_lock(&data_lock);
    
    for (int i = 0; i < global_count; i++) {
        if (global_images[i].id == id) {
            char response[512];
            snprintf(response, sizeof(response),
                "{\"found\":true,\"image\":{\"id\":%d,\"filename\":\"%s\",\"width\":%d,\"height\":%d,\"size_kb\":%.2f,\"bit_depth\":%d}}",
                global_images[i].id,
                global_images[i].filename,
                global_images[i].width,
                global_images[i].height,
                global_images[i].size_kb,
                global_images[i].bit_depth
            );
            pthread_mutex_unlock(&data_lock);
            send_json_response(client_fd, 200, response);
            return;
        }
    }
    
    pthread_mutex_unlock(&data_lock);
    send_json_response(client_fd, 404, "{\"found\":false}");
}

void handle_delete_image(int client_fd, const char* query) {
    int id = -1;
    const char* id_str = strstr(query, "id=");
    if (id_str) {
        id = atoi(id_str + 3);
    }

    if (id == -1) {
        send_error(client_fd, "Invalid or missing ID");
        return;
    }

    pthread_mutex_lock(&data_lock);

    int found_index = -1;
    for (int i = 0; i < global_count; i++) {
        if (global_images[i].id == id) {
            found_index = i;
            break;
        }
    }

    if (found_index != -1) {
        // Delete file
        char filepath[256];
        snprintf(filepath, sizeof(filepath), "%s/%s", UPLOAD_DIR, global_images[found_index].filename);
        remove(filepath);

        // Delete from array
        for (int j = found_index; j < global_count - 1; j++) {
            global_images[j] = global_images[j + 1];
        }
        global_count--;
        global_images = realloc(global_images, global_count * sizeof(Image));


        saveCSV("data/images.csv", global_images, global_count);

        pthread_mutex_unlock(&data_lock);
        send_json_response(client_fd, 200, "{\"success\":true,\"message\":\"Image deleted\"}");
    } else {
        pthread_mutex_unlock(&data_lock);
        send_error(client_fd, "Image not found");
    }
}

void handle_sort_images(int client_fd, const char* query) {
    int sort_type = 1; // default by ID
    sscanf(query, "type=%d", &sort_type);
    
    pthread_mutex_lock(&data_lock);
    
    if (global_images && global_count > 0) {
        sort_images(global_images, global_count, sort_type);
        saveCSV("data/images.csv", global_images, global_count);
    }
    
    pthread_mutex_unlock(&data_lock);
    send_json_response(client_fd, 200, "{\"success\":true,\"message\":\"Images sorted\"}");
}

void handle_load_csv(int client_fd) {
    pthread_mutex_lock(&data_lock);
    
    if (global_images) {
        free(global_images);
    }
    
    global_images = loadCSV("data/images.csv", &global_count);
    
    pthread_mutex_unlock(&data_lock);
    
    char response[256];
    snprintf(response, sizeof(response), "{\"success\":true,\"message\":\"CSV loaded\",\"count\":%d}", global_count);
    send_json_response(client_fd, 200, response);
}

// Parse HTTP request and route
void* handle_client(void* arg) {
    int client_fd = *(int*)arg;
    free(arg);
    
    char buffer[BUFFER_SIZE];
    memset(buffer, 0, BUFFER_SIZE);
    
    ssize_t bytes = recv(client_fd, buffer, BUFFER_SIZE - 1, 0);
    if (bytes <= 0) {
        close(client_fd);
        return NULL;
    }
    
    buffer[bytes] = '\0';
    
    // Parse request
    char method[10], path[256], protocol[20];
    sscanf(buffer, "%s %s %s", method, path, protocol);
    
    // CORS preflight
    if (strcmp(method, "OPTIONS") == 0) {
        char response[] = 
            "HTTP/1.1 200 OK\r\n"
            "Access-Control-Allow-Origin: *\r\n"
            "Access-Control-Allow-Methods: GET, POST, DELETE, OPTIONS\r\n"
            "Access-Control-Allow-Headers: Content-Type, multipart/form-data\r\n"
            "Content-Length: 0\r\n"
            "Connection: close\r\n"
            "\r\n";
        send(client_fd, response, strlen(response), 0);
        close(client_fd);
        return NULL;
    }
    
    // Extract query string
    char* query = strchr(path, '?');
    if (query) {
        *query = '\0'; // Null-terminate the path
        query++;     // The query string starts after '?'
    } else {
        query = "";
    }
    
    // Extract body if POST
    char* body = strstr(buffer, "\r\n\r\n");
    if (body) {
        body += 4;
    } else {
        body = buffer + bytes; // Should not happen with valid HTTP
    }
     ssize_t body_size = bytes - (body - buffer);

    
    // Route requests
    if (strcmp(method, "GET") == 0) {
        if (strcmp(path, "/api/images") == 0) {
            handle_get_images(client_fd);
        } else if (strncmp(path, "/api/image/", 11) == 0) {
            handle_get_image(client_fd, path + 11);
        } else if (strncmp(path, "/api/download/", 14) == 0) {
            handle_download_image(client_fd, path + 14);
        } else if (strcmp(path, "/api/search") == 0) {
            handle_search_image(client_fd, query);
        } else if (strcmp(path, "/api/sort") == 0) {
            handle_sort_images(client_fd, query);
        } else if (strcmp(path, "/api/load") == 0) {
            handle_load_csv(client_fd);
        } else {
            send_error(client_fd, "Endpoint not found");
        }
    } else if (strcmp(method, "POST") == 0) {
        if (strcmp(path, "/api/upload") == 0) {
            handle_upload_image(client_fd, buffer, bytes);
        } else {
            send_error(client_fd, "Endpoint not found");
        }
    } else if (strcmp(method, "DELETE") == 0) {
        if (strcmp(path, "/api/images") == 0) {
            handle_delete_image(client_fd, query);
        } else {
            send_error(client_fd, "Endpoint not found");
        }
    } else {
        send_error(client_fd, "Method not allowed");
    }
    
    close(client_fd);
    return NULL;
}

int main() {
    // Ensure upload directory exists
    ensure_upload_dir();
    
    // Load initial data
    global_images = loadCSV("data/images.csv", &global_count);
    
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("Socket creation failed");
        return 1;
    }
    
    // Allow socket reuse
    int opt = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        perror("setsockopt failed");
        return 1;
    }
    
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    
    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        return 1;
    }
    
    if (listen(server_fd, MAX_CLIENTS) < 0) {
        perror("Listen failed");
        return 1;
    }
    
    printf("HTTP API Server running on http://localhost:%d\n", PORT);
    printf("Endpoints:\n");
    printf("  GET    /api/images           - Get all images\n");
    printf("  POST   /api/upload           - Upload image file\n");
    printf("  GET    /api/image/{id}       - View image\n");
    printf("  GET    /api/download/{id}    - Download image\n");
    printf("  GET    /api/search?id=X      - Search image by ID\n");
    printf("  DELETE /api/images?id=X      - Delete image by ID\n");
    printf("  GET    /api/sort?type=X      - Sort images\n");
    printf("  GET    /api/load             - Load CSV\n");
    
    while (1) {
        struct sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);
        
        int client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &client_len);
        if (client_fd < 0) {
            perror("Accept failed");
            continue;
        }
        
        int* client_ptr = malloc(sizeof(int));
        *client_ptr = client_fd;
        
        pthread_t thread_id;
        if (pthread_create(&thread_id, NULL, handle_client, client_ptr) != 0) {
            perror("Thread creation failed");
            free(client_ptr);
            close(client_fd);
        }
        pthread_detach(thread_id);
    }
    
    close(server_fd);
    if (global_images) free(global_images);
    return 0;
}
