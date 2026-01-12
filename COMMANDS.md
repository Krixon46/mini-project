# Terminal Commands - Complete Guide

## 🚀 First Time Setup (Run Once)

Copy and paste these commands in order:

### 1. Navigate to backend and compile
```bash
cd "/media/archisman-banerjee/New Volume/mini/mini-project/backend"
make clean
make
```

Expected output:
```
gcc -Wall -Wextra -pthread -O2 -c src/http_server.c -o src/http_server.o
gcc -Wall -Wextra -pthread -O2 -c src/csv.c -o src/csv.o
gcc -Wall -Wextra -pthread -O2 -c src/array_ops.c -o src/array_ops.o
gcc -Wall -Wexist -pthread -O2 -c src/sort.c -o src/sort.o
gcc -o build/http_server src/http_server.o src/csv.o src/array_ops.o src/sort.o -pthread
```

---

## ⚡ Running the Application (Every Time)

### Terminal 1: Start Backend API Server
```bash
cd "/media/archisman-banerjee/New Volume/mini/mini-project/backend"
./build/http_server
```

**Expected output:**
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

✅ **Keep this terminal running!**

---

### Terminal 2: Start Frontend Web Server
```bash
cd "/media/archisman-banerjee/New Volume/mini/mini-project/frontend"
python3 -m http.server 3000
```

**Expected output:**
```
Serving HTTP on 0.0.0.0 port 3000 (http://0.0.0.0:3000/) ...
```

✅ **Keep this terminal running too!**

---

### Terminal 3 (Optional): Test the API

Test if API is working:

```bash
# Get all images
curl http://localhost:8080/api/images

# Add a test image
curl -X POST http://localhost:8080/api/images \
  -H "Content-Type: application/json" \
  -d '{"id":99,"filename":"test.jpg","width":1024,"height":768,"size_kb":200,"bit_depth":24}'

# Search
curl http://localhost:8080/api/search?id=1

# Sort by height
curl http://localhost:8080/api/sort?type=4
```

---

## 🌐 Access the Application

Open any web browser and go to:
```
http://localhost:3000
```

---

## 🛑 Stopping the Application

### To stop Backend (Terminal 1):
```
Press Ctrl+C
```

### To stop Frontend (Terminal 2):
```
Press Ctrl+C
```

---

## 🔄 Rebuilding (if you modify code)

```bash
cd "/media/archisman-banerjee/New Volume/mini/mini-project/backend"
make clean
make
```

---

## 📋 One-Liner Commands

**Just copy-paste these without any setup:**

### Open everything at once (requires multiple terminals or tmux):

```bash
# Terminal 1
cd "/media/archisman-banerjee/New Volume/mini/mini-project/backend" && ./build/http_server
```

```bash
# Terminal 2
cd "/media/archisman-banerjee/New Volume/mini/mini-project/frontend" && python3 -m http.server 3000
```

Then open: `http://localhost:3000`

---

## 🐛 Troubleshooting Commands

### Check if port 8080 is in use:
```bash
lsof -i :8080
```

### Check if port 3000 is in use:
```bash
lsof -i :3000
```

### Kill process on specific port (replace 8080 with port number):
```bash
kill $(lsof -t -i :8080)
```

### Verify backend is running:
```bash
curl -v http://localhost:8080/api/images
```

### View CSV data:
```bash
cat "/media/archisman-banerjee/New Volume/mini/mini-project/backend/data/images.csv"
```

### Edit CSV directly:
```bash
nano "/media/archisman-banerjee/New Volume/mini/mini-project/backend/data/images.csv"
```

---

## 📊 Complete Workflow Example

1. **Compile (first time only):**
   ```bash
   cd "/media/archisman-banerjee/New Volume/mini/mini-project/backend" && make clean && make
   ```

2. **Open Terminal 1 - Start Backend:**
   ```bash
   cd "/media/archisman-banerjee/New Volume/mini/mini-project/backend" && ./build/http_server
   ```

3. **Open Terminal 2 - Start Frontend:**
   ```bash
   cd "/media/archisman-banerjee/New Volume/mini/mini-project/frontend" && python3 -m http.server 3000
   ```

4. **Open Browser:**
   - Go to `http://localhost:3000`
   - Start adding/managing images!

5. **When Done - Stop both servers:**
   - Terminal 1: Press `Ctrl+C`
   - Terminal 2: Press `Ctrl+C`

---

## 🎯 Common Operations

### Add an image via API
```bash
curl -X POST http://localhost:8080/api/images \
  -H "Content-Type: application/json" \
  -d '{
    "id": 100,
    "filename": "nature.jpg",
    "width": 3840,
    "height": 2160,
    "size_kb": 1500.50,
    "bit_depth": 24
  }'
```

### Get all images
```bash
curl http://localhost:8080/api/images | python3 -m json.tool
```

### Delete an image
```bash
curl -X DELETE "http://localhost:8080/api/images?id=100"
```

### Sort by filename
```bash
curl "http://localhost:8080/api/sort?type=2"
```

### Search for image
```bash
curl "http://localhost:8080/api/search?id=1" | python3 -m json.tool
```

---

## 📝 Notes

- Backend runs on **port 8080**
- Frontend runs on **port 3000**
- Data is stored in **`backend/data/images.csv`**
- Frontend is pure HTML/CSS/JS (no build step needed)
- Backend is C with pthread support
- All API responses are JSON format
- CORS is enabled for cross-origin requests
