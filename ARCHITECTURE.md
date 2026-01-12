# Architecture & System Overview

## System Architecture Diagram

```
┌─────────────────────────────────────────────────────────────────┐
│                         WEB BROWSER                              │
│                    (http://localhost:3000)                       │
│  ┌──────────────────────────────────────────────────────────┐   │
│  │                   Frontend (index.html)                   │   │
│  │  - HTML5 Interface                                        │   │
│  │  - CSS3 Styling                                           │   │
│  │  - Vanilla JavaScript (Fetch API)                         │   │
│  │                                                            │   │
│  │  Features:                                                │   │
│  │  • Add new images                                         │   │
│  │  • View all images                                        │   │
│  │  • Search by ID                                           │   │
│  │  • Delete images                                          │   │
│  │  • Sort by 6 criteria                                     │   │
│  │  • Real-time statistics                                   │   │
│  └──────────────────────────────────────────────────────────┘   │
└─────────────────────────────────────────────────────────────────┘
                              ↕ HTTP Requests/Responses
                              (JSON)
┌─────────────────────────────────────────────────────────────────┐
│                    BACKEND API SERVER                            │
│              (http://localhost:8080, C + pthread)               │
│  ┌──────────────────────────────────────────────────────────┐   │
│  │                   http_server.c                           │   │
│  │                                                            │   │
│  │  HTTP Server (Port 8080)                                  │   │
│  │  ├── GET  /api/images      → Get all images              │   │
│  │  ├── POST /api/images      → Add new image               │   │
│  │  ├── GET  /api/search?id=X → Search by ID                │   │
│  │  ├── DELETE /api/images?id=X → Delete                    │   │
│  │  ├── GET  /api/sort?type=X → Sort                        │   │
│  │  └── GET  /api/load        → Load CSV                    │   │
│  │                                                            │   │
│  │  Features:                                                │   │
│  │  • Multi-threaded (pthread)                               │   │
│  │  • Thread-safe (mutex locks)                              │   │
│  │  • CORS enabled                                           │   │
│  │  • JSON responses                                         │   │
│  └──────────────────────────────────────────────────────────┘   │
│                              ↕                                    │
│  ┌──────────────────────────────────────────────────────────┐   │
│  │              C Backend Libraries                          │   │
│  │                                                            │   │
│  │  csv.c/csv.h        → Load/Save CSV files                │   │
│  │  array_ops.c/h      → Add/Delete/Display operations      │   │
│  │  sort.c/sort.h      → Sort by 6 different criteria       │   │
│  └──────────────────────────────────────────────────────────┘   │
│                              ↕                                    │
│  ┌──────────────────────────────────────────────────────────┐   │
│  │           Data Storage (CSV File)                         │   │
│  │      backend/data/images.csv                              │   │
│  │                                                            │   │
│  │  Format:                                                  │   │
│  │  id,filename,width,height,size_kb,bit_depth              │   │
│  │  1,photo.jpg,1920,1080,500.5,24                          │   │
│  │  2,image.png,800,600,150.25,32                           │   │
│  └──────────────────────────────────────────────────────────┘   │
└─────────────────────────────────────────────────────────────────┘
```

---

## Data Flow Diagram

### Adding an Image
```
User Input (Form)
        ↓
JavaScript Fetch API
        ↓
HTTP POST /api/images (JSON)
        ↓
http_server.c (handle_add_image)
        ↓
Realloc memory for new image
        ↓
Parse JSON & populate Image struct
        ↓
Write to global_images array
        ↓
Call saveCSV()
        ↓
Update images.csv file
        ↓
Return JSON response {success: true}
        ↓
JavaScript updates UI
        ↓
User sees new image in list
```

### Fetching All Images
```
User clicks "Refresh"
        ↓
JavaScript Fetch API
        ↓
HTTP GET /api/images
        ↓
http_server.c (handle_get_images)
        ↓
Lock mutex (thread-safe)
        ↓
Iterate through global_images array
        ↓
Build JSON response
        ↓
Unlock mutex
        ↓
Return JSON array
        ↓
JavaScript parses response
        ↓
Render images in UI
        ↓
Update statistics
```

### Sorting Images
```
User selects sort criteria
        ↓
JavaScript Fetch API
        ↓
HTTP GET /api/sort?type=4
        ↓
http_server.c (handle_sort_images)
        ↓
Lock mutex
        ↓
Call sort_images() from sort.c
        ↓
qsort() by selected criterion
        ↓
Call saveCSV() to persist
        ↓
Unlock mutex
        ↓
Return success response
        ↓
JavaScript reloads image list
        ↓
Sorted images displayed
```

---

## File Structure with Descriptions

```
mini-project/
│
├── backend/
│   ├── build/
│   │   └── http_server          [Compiled executable - Run this!]
│   │
│   ├── src/
│   │   ├── http_server.c        [NEW] HTTP API Server - Main backend
│   │   ├── csv.c/h              [Loads/saves CSV files]
│   │   ├── array_ops.c/h        [Add/Delete/Display operations]
│   │   ├── sort.c/h             [Sorting by 6 criteria]
│   │   └── menu.c/h             [Original menu system - not used by API]
│   │
│   ├── data/
│   │   └── images.csv           [Database file - persists data]
│   │
│   └── Makefile                 [NEW] Compilation rules
│
├── frontend/
│   └── index.html               [NEW] Complete web UI - Open in browser
│
├── COMMANDS.md                  [NEW] All terminal commands
├── SETUP.md                     [NEW] Setup & installation guide
├── QUICKSTART.md                [NEW] Quick start instructions
├── API_DOCS.md                  [NEW] Detailed API documentation
└── README.md                    [Original project description]
```

---

## Technology Stack

```
Frontend Layer
├── HTML5 (Structure)
├── CSS3 (Styling with gradients, animations, grid)
└── Vanilla JavaScript (No frameworks - Fetch API)

API Layer (HTTP/REST/JSON)
└── RESTful endpoints on port 8080

Backend Layer
├── C Programming Language
├── POSIX Threads (pthread)
├── Socket API (TCP/IP)
├── Mutex locks (Thread safety)
├── Dynamic arrays (malloc/realloc)
└── Standard library (stdio, stdlib, string.h)

Data Layer
└── CSV file format (Simple text-based database)
```

---

## Threading Model

```
Main Thread (http_server.c)
    ↓
socket() - Create server socket
    ↓
bind() - Bind to port 8080
    ↓
listen() - Listen for connections
    ↓
accept() - Accept client connections
    ↓
For each client:
    └─→ pthread_create() - Create new thread
            ↓
        handle_client() function
            ↓
        Parse HTTP request
            ↓
        Lock mutex
            ↓
        Access global_images
            ↓
        Unlock mutex
            ↓
        Send JSON response
            ↓
        pthread_detach() - Clean up thread
            ↓
        close() - Close client socket
```

---

## API Response Flow

```
Frontend Request
    ↓
    ↓─ Validation (JavaScript)
    ↓
    ↓─ HTTP Request (GET/POST/DELETE)
    ↓
Backend Handler
    ↓
    ├─ Parse HTTP request
    ├─ Extract method & path & body
    ├─ Route to appropriate handler
    ├─ Lock mutex for thread safety
    ├─ Perform operation (Read/Write/Delete/Sort)
    ├─ Unlock mutex
    └─ Build JSON response
    ↓
HTTP Response
    ├─ HTTP Status Code
    ├─ CORS Headers
    ├─ Content-Type: application/json
    └─ JSON Body
    ↓
Frontend Receives
    ├─ Parse JSON
    ├─ Update DOM
    ├─ Show notifications
    └─ Reflect changes to user
```

---

## Performance Characteristics

| Operation | Time Complexity | Details |
|-----------|-----------------|---------|
| GET /images | O(n) | Iterates through all images to build JSON |
| POST /images | O(1) | Append to dynamic array + CSV write |
| GET /search | O(n) | Linear search through array |
| DELETE | O(n) | Find and shift elements |
| SORT | O(n log n) | Uses qsort (quicksort) |
| CSV Load | O(n) | Reads file line by line |
| CSV Save | O(n) | Writes all records to file |

Where n = number of images

---

## Security Considerations

### Current Implementation
- ✅ Thread-safe operations (mutex locks)
- ✅ CORS enabled for frontend integration
- ✅ Input validation (JSON parsing)
- ✅ No command injection (uses structured data)

### Production Improvements (Future)
- Add authentication/authorization
- Implement rate limiting
- Add input sanitization
- Use HTTPS instead of HTTP
- Implement database instead of CSV
- Add request logging

---

## Deployment Diagram

```
Development Machine
┌─────────────────────────────────────────┐
│  Terminal 1: Backend Server             │
│  ./build/http_server                    │
│  Port: 8080                             │
└─────────────────────────────────────────┘
            ↕ Localhost Network
┌─────────────────────────────────────────┐
│  Terminal 2: Frontend Server            │
│  python3 -m http.server 3000            │
│  Port: 3000                             │
└─────────────────────────────────────────┘
            ↕ HTTP
┌─────────────────────────────────────────┐
│  Browser                                │
│  http://localhost:3000                  │
└─────────────────────────────────────────┘
```
