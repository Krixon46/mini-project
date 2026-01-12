# 🎯 VISUAL QUICK START

## Three Steps to Run Everything

```
┌─────────────────────────────────────────────────────────────┐
│  STEP 1: COMPILE (First time only)                          │
│                                                             │
│  Copy-paste this command:                                   │
│  ─────────────────────────────────────────────────────────  │
│  cd "/media/archisman-banerjee/New Volume/mini/mini-project │
│  /backend" && make clean && make                            │
│                                                             │
│  ✓ You should see: gcc compilation commands               │
│  ✓ Result: build/http_server file created                 │
└─────────────────────────────────────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────────┐
│  STEP 2: START BACKEND (Terminal 1)                         │
│                                                             │
│  Copy-paste this command:                                   │
│  ─────────────────────────────────────────────────────────  │
│  cd "/media/archisman-banerjee/New Volume/mini/mini-project │
│  /backend" && ./build/http_server                           │
│                                                             │
│  ✓ You should see: "HTTP API Server running on port 8080" │
│  ✓ ⚠️ Keep this terminal open!                             │
└─────────────────────────────────────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────────┐
│  STEP 3: START FRONTEND (Terminal 2)                        │
│                                                             │
│  Copy-paste this command:                                   │
│  ─────────────────────────────────────────────────────────  │
│  cd "/media/archisman-banerjee/New Volume/mini/mini-project │
│  /frontend" && python3 -m http.server 3000                 │
│                                                             │
│  ✓ You should see: "Serving HTTP on ... port 3000"        │
│  ✓ ⚠️ Keep this terminal open!                             │
└─────────────────────────────────────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────────┐
│  STEP 4: OPEN BROWSER                                       │
│                                                             │
│  Go to: http://localhost:3000                               │
│                                                             │
│  🎉 YOUR APP IS RUNNING! 🎉                                │
└─────────────────────────────────────────────────────────────┘
```

---

## 📱 What You'll See in Browser

```
┌────────────────────────────────────────────────────────────┐
│  🖼️ Image Metadata Manager                                  │
│  Upload, manage, and organize your image metadata           │
├────────────────────────────────────────────────────────────┤
│                                                            │
│  ┌──────────────────────┐  ┌─────────────────────────────┐ │
│  │ ➕ ADD IMAGE         │  │ 📊 STATISTICS               │ │
│  │ ─────────────────────│  │ ─────────────────────────────│ │
│  │ Image ID: [_____]    │  │  Total: 5 images            │ │
│  │ Filename: [_____]    │  │  Size: 2500.50 KB           │ │
│  │ Width: [_____]       │  │                             │ │
│  │ Height: [_____]      │  │ 📁 ALL IMAGES               │ │
│  │ Size: [_____]        │  │ ─────────────────────────────│ │
│  │ Bit Depth: [__▼]     │  │ [Refresh] [Sort ▼]          │ │
│  │ [Add] [Clear]        │  │ ─────────────────────────────│ │
│  │                      │  │ Image #1: photo.jpg         │ │
│  │ 🔍 SEARCH            │  │ 1920x1080, 500.5KB [Delete] │ │
│  │ ─────────────────────│  │                             │ │
│  │ Enter ID: [_____]    │  │ Image #2: image.png         │ │
│  │ [Search]             │  │ 800x600, 150.25KB [Delete]  │ │
│  │                      │  │ ... more images ...         │ │
│  └──────────────────────┘  └─────────────────────────────┘ │
│                                                            │
└────────────────────────────────────────────────────────────┘
```

---

## 🔄 What Each Command Does

```
┌─────────────────────────────┐
│  COMPILE                    │
│  ─────────────────────────  │
│  make clean                 │ ← Remove old files
│  make                       │ ← Compile C code
│                             │
│  Result: build/http_server  │ ← Executable
└─────────────────────────────┘
           ↓
┌─────────────────────────────┐
│  BACKEND (Terminal 1)       │
│  ─────────────────────────  │
│  ./build/http_server        │ ← Start API server
│                             │
│  Listens on port 8080       │ ← Ready for requests
│  Auto-loads images.csv      │ ← Database ready
│  Waits for connections      │ ← Ready to serve
└─────────────────────────────┘
           ↓
┌─────────────────────────────┐
│  FRONTEND (Terminal 2)      │
│  ─────────────────────────  │
│  python3 -m http.server     │ ← Web server
│  port 3000                  │
│                             │
│  Serves index.html          │ ← Serves files
│  Waits for browser          │ ← Ready for users
└─────────────────────────────┘
           ↓
┌─────────────────────────────┐
│  BROWSER                    │
│  ─────────────────────────  │
│  http://localhost:3000      │ ← Open this URL
│                             │
│  Loads HTML/CSS/JS          │ ← Beautiful UI
│  Connects to backend        │ ← Communicates
│  Shows your data            │ ← Ready to use!
└─────────────────────────────┘
```

---

## 📊 Data Flow

```
USER ACTION
    ↓
JavaScript Fetch API
    ↓
HTTP Request to localhost:8080
    ↓
http_server.c receives request
    ↓
Parse & route to handler
    ↓
Lock mutex for safety
    ↓
Access image data
    ↓
Perform operation (GET/POST/DELETE)
    ↓
Update CSV if needed
    ↓
Unlock mutex
    ↓
Build JSON response
    ↓
Send back to frontend
    ↓
JavaScript updates UI
    ↓
User sees changes instantly
```

---

## 🎮 Using the App

### Add Image
```
1. Fill the form on left
   • Image ID
   • Filename
   • Width & Height
   • Size in KB
   • Bit Depth
   
2. Click "Add Image"

3. Image appears in right panel

4. CSV file updated automatically
```

### View Images
```
1. Click "Refresh" button

2. All images from database shown

3. Statistics updated automatically

4. Each image shows: ID, filename, dimensions, size, depth
```

### Search Image
```
1. Enter Image ID

2. Click "Search"

3. Result appears below

4. Shows full details if found
```

### Sort Images
```
1. Select sort option from dropdown

2. Click "Sort" button

3. Images reordered

4. CSV saved with new order
```

### Delete Image
```
1. Click "Delete" button on image

2. Confirm deletion

3. Image removed

4. CSV updated
```

---

## 🔍 Behind the Scenes

```
When you click "Add Image":

Frontend                        Backend
──────────                      ───────
1. Validate form    ────→  2. Receive JSON
                               
3. Send HTTP POST              4. Parse data
                               
                          5. Lock mutex
                          
                          6. Add to array
                          
                          7. Save to CSV
                          
                          8. Unlock mutex
                               
         ←──── 9. Send JSON response
                               
10. Parse response              
                               
11. Update UI                   
                               
12. Show success message        
```

---

## ✅ Verification Steps

```
After starting everything:

1. Backend Running?
   $ curl http://localhost:8080/api/images
   ✓ Should return JSON list

2. Frontend Running?
   $ curl http://localhost:3000
   ✓ Should return HTML page

3. Browser Working?
   Open http://localhost:3000
   ✓ Should show beautiful UI

4. API Working?
   Add an image via UI
   ✓ Should appear in list
   ✓ Should save to images.csv

5. Everything OK?
   You're good to go! 🚀
```

---

## 📋 Troubleshooting Visual Guide

```
❌ "Connection refused"
   └─→ Backend not running
   └─→ Solution: Start ./build/http_server in Terminal 1

❌ "Cannot GET /"
   └─→ Frontend not running
   └─→ Solution: Start python3 -m http.server in Terminal 2

❌ "Port already in use"
   └─→ Something else using the port
   └─→ Solution: Kill old process or change port

❌ "Compilation errors"
   └─→ Missing gcc
   └─→ Solution: sudo apt-get install build-essential

❌ "No data shows"
   └─→ CSV file issue
   └─→ Solution: Check backend/data/images.csv exists

❌ "Still not working?"
   └─→ Check browser console (F12)
   └─→ Check terminal output
   └─→ Read the documentation files
```

---

## 🎯 Success Criteria

Your setup is correct when:

✅ Terminal 1 shows: "HTTP API Server running on http://localhost:8080"
✅ Terminal 2 shows: "Serving HTTP on 0.0.0.0 port 3000"
✅ Browser loads: http://localhost:3000 (beautiful UI visible)
✅ Statistics show: Some images loaded
✅ Can add image: Form works, image appears
✅ Can search: Find existing images
✅ Can delete: Remove images
✅ Can sort: Reorder images
✅ CSV updates: backend/data/images.csv changes

If all ✅, you're done! 🎉

---

## 📞 Need Help?

```
Problem                    Solution
──────────────────────────────────────────────────────
Backend won't start        → Make sure port 8080 is free
                          → Check ./build/http_server exists

Frontend won't load        → Make sure port 3000 is free
                          → Check index.html exists

No data displayed          → Click "Refresh" button
                          → Check backend is running

API not responding         → curl http://localhost:8080/api/images
                          → Check terminal for errors

Still stuck?               → Read 00_READ_ME_FIRST.md
                          → Read QUICKSTART.md
                          → Check COMMANDS.md
```

---

## 🚀 You're Ready!

Just run these three commands in order and you're done! 🎉

1️⃣  Compile
2️⃣  Start Backend
3️⃣  Start Frontend
4️⃣  Open Browser

That's it! Enjoy your app! 🎊
