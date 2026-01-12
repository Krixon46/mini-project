# Quick Start Guide

## 📋 Terminal Commands to Run Everything

### Step 1: Build the Backend Server (Run Once)
```bash
cd /media/archisman-banerjee/New\ Volume/mini/mini-project/backend
make clean
make
```

### Step 2: Start the Backend API Server (Terminal 1)
```bash
cd /media/archisman-banerjee/New\ Volume/mini/mini-project/backend
./build/http_server
```

Wait for output:
```
HTTP API Server running on http://localhost:8080
```

### Step 3: Start Frontend Server (Terminal 2)
```bash
cd /media/archisman-banerjee/New\ Volume/mini/mini-project/frontend
python3 -m http.server 3000
```

### Step 4: Open in Browser
```
http://localhost:3000
```

---

## 🎯 What Each Component Does

### Backend HTTP Server (`http_server.c`)
- Listens on port 8080
- Handles HTTP requests from frontend
- Manages image data (CRUD operations)
- Returns JSON responses
- Thread-safe with mutex locks
- Automatically saves to CSV

### Frontend (`index.html`)
- Beautiful, responsive web UI
- Add/view/search/delete images
- Sort images by different criteria
- Real-time statistics
- Communicates with backend via REST API

---

## 🔧 API Quick Reference

All URLs: `http://localhost:8080/api/`

| Action | Command |
|--------|---------|
| **View All** | `GET /images` |
| **Add Image** | `POST /images` (with JSON body) |
| **Search** | `GET /search?id=1` |
| **Delete** | `DELETE /images?id=1` |
| **Sort** | `GET /sort?type=4` (1-6) |
| **Reload CSV** | `GET /load` |

---

## 📝 Example: Add Image via API

Using curl:
```bash
curl -X POST http://localhost:8080/api/images \
  -H "Content-Type: application/json" \
  -d '{"id":1,"filename":"test.jpg","width":1920,"height":1080,"size_kb":250,"bit_depth":24}'
```

Using fetch (JavaScript):
```javascript
fetch('http://localhost:8080/api/images', {
  method: 'POST',
  headers: { 'Content-Type': 'application/json' },
  body: JSON.stringify({
    id: 1,
    filename: 'photo.jpg',
    width: 1920,
    height: 1080,
    size_kb: 500.5,
    bit_depth: 24
  })
})
```

---

## ⚠️ Common Issues & Fixes

| Problem | Solution |
|---------|----------|
| "Connection refused" | Backend not running - check Terminal 1 |
| "Port 8080 in use" | Change port in `http_server.c` line with `#define PORT` |
| Frontend loads but no data | Make sure backend server is running first |
| CSV file not found | Create `backend/data/images.csv` with header: `id,filename,width,height,size_kb,bit_depth` |

---

## 🎨 Frontend Pages/Sections

1. **Add New Image** - Form to add images
2. **Search Image** - Find image by ID
3. **Statistics** - Total count & size
4. **All Images** - View, sort, delete images

---

## 💡 Tips

- Always start backend BEFORE frontend
- Use browser DevTools (F12) to see network requests
- Check terminal output for error messages
- CSV is updated automatically after add/delete/sort operations
