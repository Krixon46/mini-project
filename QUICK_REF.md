# ⚡ QUICK REFERENCE CARD

## 🎯 Three Commands to Start Everything

### Compile (First Time Only)
```bash
cd "/media/archisman-banerjee/New Volume/mini/mini-project/backend" && make clean && make
```

### Terminal 1: Backend
```bash
cd "/media/archisman-banerjee/New Volume/mini/mini-project/backend" && ./build/http_server
```

### Terminal 2: Frontend
```bash
cd "/media/archisman-banerjee/New Volume/mini/mini-project/frontend" && python3 -m http.server 3000
```

### Browser
```
http://localhost:3000
```

---

## 🔌 API Quick Reference

| Action | Command |
|--------|---------|
| **List All** | `curl http://localhost:8080/api/images` |
| **Add** | `curl -X POST ... /api/images -d '{...}'` |
| **Search** | `curl http://localhost:8080/api/search?id=1` |
| **Delete** | `curl -X DELETE http://localhost:8080/api/images?id=1` |
| **Sort** | `curl http://localhost:8080/api/sort?type=4` |

---

## 📝 Add Image JSON Format

```json
{
  "id": 1,
  "filename": "photo.jpg",
  "width": 1920,
  "height": 1080,
  "size_kb": 500.5,
  "bit_depth": 24
}
```

---

## 🎨 Frontend Features

| Feature | Location |
|---------|----------|
| Add Images | Left Panel |
| Search | Left Panel |
| View All | Right Panel |
| Statistics | Right Panel |
| Sort | Dropdown in Right Panel |
| Delete | Button on each image |

---

## 📊 Sort Types

| Type | Value |
|------|-------|
| By ID | 1 |
| By Filename | 2 |
| By Width | 3 |
| By Height | 4 |
| By Size | 5 |
| By Bit Depth | 6 |

---

## 🔧 Key Ports

| Service | Port | URL |
|---------|------|-----|
| Backend API | 8080 | http://localhost:8080 |
| Frontend | 3000 | http://localhost:3000 |

---

## 💾 Database File

```
Location: backend/data/images.csv

Format:
id,filename,width,height,size_kb,bit_depth
1,photo.jpg,1920,1080,500.5,24
2,image.png,800,600,150.25,32
```

---

## 🛑 Stop Server

```
Press Ctrl+C in the terminal running the server
```

---

## 🧪 Quick Test

```bash
# Check backend is running
curl http://localhost:8080/api/images

# Add a test image
curl -X POST http://localhost:8080/api/images \
  -H "Content-Type: application/json" \
  -d '{"id":999,"filename":"test.jpg","width":800,"height":600,"size_kb":100,"bit_depth":24}'

# Check it was added
curl http://localhost:8080/api/images
```

---

## 📚 Documentation

| File | Content |
|------|---------|
| COMMANDS.md | All terminal commands |
| QUICKSTART.md | 5-minute setup |
| SETUP.md | Detailed guide |
| API_DOCS.md | API reference |
| ARCHITECTURE.md | System design |
| PROJECT_SUMMARY.md | Overview |

---

## 💡 Common Tasks

### View CSV Data
```bash
cat "backend/data/images.csv"
```

### Edit CSV Directly
```bash
nano "backend/data/images.csv"
```

### Check if Ports Are Free
```bash
lsof -i :8080
lsof -i :3000
```

### Kill Process on Port
```bash
kill $(lsof -t -i :8080)
```

---

## ✅ Checklist

Before you start:
- [ ] Read QUICKSTART.md
- [ ] Run compilation command
- [ ] Check `build/http_server` exists
- [ ] Check `frontend/index.html` exists

When running:
- [ ] Terminal 1: Backend running
- [ ] Terminal 2: Frontend running
- [ ] Browser: http://localhost:3000 opens
- [ ] Can add/view/search/delete images

---

## 🎯 First Test Sequence

1. Start backend (Terminal 1)
2. Start frontend (Terminal 2)
3. Open http://localhost:3000
4. Click "Refresh" to load existing images
5. Fill in form and click "Add Image"
6. Verify image appears in list
7. Try searching by ID
8. Try sorting
9. Try deleting

---

## 📞 Need Help?

1. Check if backend is running: `curl http://localhost:8080/api/images`
2. Check if frontend is running: `http://localhost:3000`
3. Check browser console for errors: Press F12
4. Check terminal for error messages
5. Read the documentation files
6. Verify CSV file exists: `ls backend/data/images.csv`

---

## 🚀 You're Ready!

Everything is set up. Just run the three commands and enjoy! 🎉
