# 🖼️ Image Upload Feature - Update

## What Changed

Your system now accepts **actual JPG/PNG image files** from the frontend instead of just metadata!

### Frontend Changes
- ✅ File upload input (accepts JPG, PNG)
- ✅ Image preview in real-time
- ✅ Auto-detects image dimensions
- ✅ Display uploaded images with thumbnails
- ✅ Download button for each image

### Backend Changes
- ✅ New `/api/upload` endpoint for file uploads
- ✅ New `/api/image/{id}` endpoint to view images
- ✅ New `/api/download/{id}` endpoint to download images
- ✅ Automatic image storage in `backend/images/` folder
- ✅ File size support up to 50MB
- ✅ Multipart form-data parsing

---

## How to Use

### Recompile (Required)
```bash
cd "/media/archisman-banerjee/New Volume/mini/mini-project/backend"
make clean
make
```

### Run Backend
```bash
cd "/media/archisman-banerjee/New Volume/mini/mini-project/backend"
./build/http_server
```

### Run Frontend
```bash
cd "/media/archisman-banerjee/New Volume/mini/mini-project/frontend"
python3 -m http.server 3000
```

### Use in Browser
1. Go to `http://localhost:3000`
2. Click "Select Image File" and choose a JPG/PNG
3. Image preview appears automatically
4. Dimensions are auto-filled
5. Adjust if needed and click "Upload Image"
6. Image appears in the list with thumbnail!

---

## New API Endpoints

| Method | Endpoint | Purpose |
|--------|----------|---------|
| POST | `/api/upload` | Upload image file |
| GET | `/api/image/{id}` | View/preview image |
| GET | `/api/download/{id}` | Download image file |

### Upload Example (curl)
```bash
curl -X POST http://localhost:8080/api/upload \
  -F "file=@photo.jpg" \
  -F "id=1" \
  -F "width=1920" \
  -F "height=1080" \
  -F "bit_depth=24"
```

---

## File Storage

Images are stored in: `backend/images/`

Each image is named by its ID: `1.jpg`, `2.jpg`, etc.

---

## Features

✅ Upload JPG/PNG images
✅ Auto-detect dimensions
✅ Image preview in UI
✅ View images in list
✅ Download images
✅ Delete images (removes file + metadata)
✅ Automatic file management
✅ Large file support (50MB max)

---

## That's It!

Just recompile and run. Everything else works the same!

No more manual metadata entry - just upload your images! 🎉
