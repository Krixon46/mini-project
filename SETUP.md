# Image Metadata Management System - Frontend & Backend Setup

## Project Structure
```
mini-project/
├── backend/
│   ├── src/
│   │   ├── http_server.c      (NEW - HTTP API Server)
│   │   ├── csv.c
│   │   ├── csv.h
│   │   ├── array_ops.c
│   │   ├── array_ops.h
│   │   ├── sort.c
│   │   ├── sort.h
│   │   └── menu.c
│   ├── data/
│   │   └── images.csv
│   ├── build/
│   └── Makefile               (NEW - Compilation rules)
├── frontend/
│   └── index.html             (NEW - Web UI)
└── README.md
```

## API Endpoints

The backend HTTP server exposes the following REST API endpoints on `http://localhost:8080`:

| Method | Endpoint | Description |
|--------|----------|-------------|
| GET | `/api/images` | Get all images |
| POST | `/api/images` | Add new image |
| GET | `/api/search?id=X` | Search image by ID |
| DELETE | `/api/images?id=X` | Delete image by ID |
| GET | `/api/sort?type=X` | Sort images |
| GET | `/api/load` | Load CSV file |

### Sort Types
- `1` = Sort by ID
- `2` = Sort by Filename
- `3` = Sort by Width
- `4` = Sort by Height
- `5` = Sort by Size (KB)
- `6` = Sort by Bit Depth

## Building & Running

### Step 1: Build the HTTP Server

Navigate to the backend directory and compile:

```bash
cd backend
make clean
make
```

This will compile `http_server.c` along with all supporting files and output to `build/http_server`.

### Step 2: Run the HTTP Server

```bash
cd backend
./build/http_server
```

You should see output:
```
HTTP API Server running on http://localhost:8080
Endpoints:
  GET  /api/images - Get all images
  POST /api/images - Add new image
  GET  /api/search?id=X - Search image by ID
  DELETE /api/images?id=X - Delete image by ID
  GET  /api/sort?type=X - Sort images (1=ID, 2=Filename, 3=Width, 4=Height, 5=Size, 6=BitDepth)
  GET  /api/load - Load CSV
```

### Step 3: Open Frontend

In a **new terminal**, start a simple HTTP server to serve the frontend:

```bash
cd frontend
python3 -m http.server 3000
```

Or if you're using Node.js:
```bash
cd frontend
npx http-server -p 3000
```

Or using PHP:
```bash
cd frontend
php -S localhost:3000
```

### Step 4: Access the Web Interface

Open your browser and navigate to:
```
http://localhost:3000
```

## Frontend Features

The web interface provides:

### ➕ Add New Image
- Enter image metadata (ID, filename, dimensions, size, bit depth)
- Click "Add Image" button
- Image is saved to CSV automatically

### 🔍 Search Image
- Enter image ID
- View image metadata instantly

### 📁 All Images
- View all images in the database
- See statistics (total count, total size)
- Delete images by clicking the "Delete" button
- Sort images by different criteria

### 📊 Statistics
- Total number of images
- Total size of all images combined

## API Request Examples

### Add Image (POST)
```bash
curl -X POST http://localhost:8080/api/images \
  -H "Content-Type: application/json" \
  -d '{
    "id": 1,
    "filename": "photo.jpg",
    "width": 1920,
    "height": 1080,
    "size_kb": 500.5,
    "bit_depth": 24
  }'
```

### Get All Images (GET)
```bash
curl http://localhost:8080/api/images
```

### Search Image (GET)
```bash
curl http://localhost:8080/api/search?id=1
```

### Delete Image (DELETE)
```bash
curl -X DELETE http://localhost:8080/api/images?id=1
```

### Sort Images (GET)
```bash
curl http://localhost:8080/api/sort?type=4
```

### Load CSV (GET)
```bash
curl http://localhost:8080/api/load
```

## Troubleshooting

### Port Already in Use
If port 8080 is already in use, modify the `#define PORT 8080` line in `http_server.c` to another port (e.g., 8081), then recompile.

### CORS Issues
The API server includes CORS headers to allow requests from different origins. If still having issues, ensure:
- Server is running on `http://localhost:8080`
- Frontend is accessing `http://localhost:3000`

### CSV File Issues
Make sure `backend/data/images.csv` exists with the header:
```
id,filename,width,height,size_kb,bit_depth
```

If not present, create it manually or the server will create an empty one.

### Compilation Errors
Ensure you have:
- GCC compiler: `gcc --version`
- pthread library available (usually included with GCC on Linux)

## One-Command Quick Start

After compiling once, use these terminal commands:

**Terminal 1 (Backend):**
```bash
cd /media/archisman-banerjee/New\ Volume/mini/mini-project/backend
./build/http_server
```

**Terminal 2 (Frontend):**
```bash
cd /media/archisman-banerjee/New\ Volume/mini/mini-project/frontend
python3 -m http.server 3000
```

Then open: `http://localhost:3000` in your browser.

## Technical Stack

- **Backend**: C with pthread for multithreading
- **Backend HTTP Server**: Custom HTTP server implementation (no external frameworks)
- **CSV Database**: Simple CSV file storage
- **Frontend**: HTML5, CSS3, Vanilla JavaScript (no frameworks)
- **API Protocol**: REST with JSON

## Features Implemented

✅ Load image metadata from CSV
✅ Display all images
✅ Add new images
✅ Search images by ID
✅ Delete images
✅ Sort by 6 different criteria
✅ Save data back to CSV
✅ Responsive web UI
✅ Real-time statistics
✅ CORS-enabled API
✅ Thread-safe backend operations
