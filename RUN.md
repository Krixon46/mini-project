# Running the Project Manually

This guide explains how to run the backend API server and the frontend application without using the `Makefile`.

## Backend (API Server)

The backend is a C-based HTTP server that provides the API for the frontend.

### 1. Compilation

To compile the backend, you need to have `gcc` installed. Open your terminal and run the following command from the root directory of the project (`mini-project/`):

```bash
# Create the build directory if it doesn't exist
mkdir -p backend/build

# Compile the source files and create the executable
gcc -o backend/build/http_server backend/src/http_server.c backend/src/csv.c backend/src/array_ops.c backend/src/sort.c -Wall -Wextra -pthread -O2 -D_GNU_SOURCE
```

This command compiles the necessary C source files and creates an executable file named `http_server` inside the `backend/build/` directory.

### 2. Running the Server

Once the compilation is successful, you can run the server with the following command from the project's root directory:

```bash
./backend/build/http_server
```

You should see a message indicating that the server is running on `http://localhost:8080`.

```
HTTP API Server running on http://localhost:8080
Endpoints:
  GET    /api/images           - Get all images
  POST   /api/upload           - Upload image file
...
```

**Keep this terminal window open.** The server needs to be running for the frontend to work.

## Frontend

The frontend is a single HTML file with embedded JavaScript and CSS that provides the user interface.

### 1. Open the Frontend File

To run the frontend, simply open the `frontend/index.html` file in your preferred web browser.

You can typically do this by:
*   Double-clicking the file in your file explorer.
*   Right-clicking the file and choosing "Open with" -> "Firefox", "Chrome", etc.
*   Using the command line (on most Linux systems):
    ```bash
    xdg-open frontend/index.html
    ```

### 2. Using the Application

The web page will load, and it will automatically try to connect to the backend API server that you started in the previous step. You can now use the interface to upload, view, and manage image metadata.
