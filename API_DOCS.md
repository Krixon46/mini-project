# API Documentation

## Base URL
```
http://localhost:8080/api
```

## Response Format
All responses are JSON format. Errors return HTTP status 400+, success returns 200.

---

## Endpoints

### 1. Get All Images
**Endpoint:** `GET /images`

**Description:** Retrieve all image records from the database.

**Request:**
```bash
GET /api/images
```

**Response (200 OK):**
```json
{
  "images": [
    {
      "id": 1,
      "filename": "photo.jpg",
      "width": 1920,
      "height": 1080,
      "size_kb": 500.5,
      "bit_depth": 24
    },
    {
      "id": 2,
      "filename": "image.png",
      "width": 800,
      "height": 600,
      "size_kb": 150.25,
      "bit_depth": 32
    }
  ]
}
```

---

### 2. Add Image
**Endpoint:** `POST /images`

**Description:** Add a new image record to the database.

**Request:**
```bash
POST /api/images
Content-Type: application/json

{
  "id": 3,
  "filename": "sunset.jpg",
  "width": 2560,
  "height": 1440,
  "size_kb": 750.0,
  "bit_depth": 24
}
```

**Response (200 OK):**
```json
{
  "success": true,
  "message": "Image added",
  "id": 3
}
```

**Response (400 Bad Request):**
```json
{
  "error": "Invalid JSON format"
}
```

**Parameters:**
| Field | Type | Required | Description |
|-------|------|----------|-------------|
| id | integer | Yes | Unique image identifier |
| filename | string | Yes | Image filename (max 100 chars) |
| width | integer | Yes | Image width in pixels |
| height | integer | Yes | Image height in pixels |
| size_kb | float | Yes | File size in kilobytes |
| bit_depth | integer | Yes | Color depth (8, 16, 24, or 32) |

---

### 3. Search Image
**Endpoint:** `GET /search?id={ID}`

**Description:** Search for an image by its ID.

**Request:**
```bash
GET /api/search?id=1
```

**Response (200 OK - Found):**
```json
{
  "found": true,
  "image": {
    "id": 1,
    "filename": "photo.jpg",
    "width": 1920,
    "height": 1080,
    "size_kb": 500.5,
    "bit_depth": 24
  }
}
```

**Response (404 Not Found):**
```json
{
  "found": false
}
```

**Parameters:**
| Parameter | Type | Required | Description |
|-----------|------|----------|-------------|
| id | integer | Yes | Image ID to search |

---

### 4. Delete Image
**Endpoint:** `DELETE /images?id={ID}`

**Description:** Delete an image record by its ID.

**Request:**
```bash
DELETE /api/images?id=1
```

**Response (200 OK):**
```json
{
  "success": true,
  "message": "Image deleted"
}
```

**Response (400 Bad Request):**
```json
{
  "error": "Image not found"
}
```

**Parameters:**
| Parameter | Type | Required | Description |
|-----------|------|----------|-------------|
| id | integer | Yes | Image ID to delete |

---

### 5. Sort Images
**Endpoint:** `GET /sort?type={TYPE}`

**Description:** Sort all images by a specified criterion and save results.

**Request:**
```bash
GET /api/sort?type=4
```

**Response (200 OK):**
```json
{
  "success": true,
  "message": "Images sorted"
}
```

**Parameters:**
| Parameter | Type | Required | Description |
|-----------|------|----------|-------------|
| type | integer | Yes | Sort criterion (1-6) |

**Sort Types:**
| Type | Field |
|------|-------|
| 1 | ID (ascending) |
| 2 | Filename (alphabetical) |
| 3 | Width (ascending) |
| 4 | Height (ascending) |
| 5 | Size in KB (ascending) |
| 6 | Bit Depth (ascending) |

---

### 6. Load CSV
**Endpoint:** `GET /load`

**Description:** Reload the CSV file from disk. Useful after external modifications.

**Request:**
```bash
GET /api/load
```

**Response (200 OK):**
```json
{
  "success": true,
  "message": "CSV loaded",
  "count": 5
}
```

---

## HTTP Status Codes

| Code | Meaning |
|------|---------|
| 200 | OK - Request successful |
| 400 | Bad Request - Invalid input or missing parameters |
| 404 | Not Found - Resource doesn't exist |
| 405 | Method Not Allowed - Wrong HTTP method |

---

## Error Responses

All errors follow this format:

**Format:**
```json
{
  "error": "Error message describing what went wrong"
}
```

**Common Errors:**
```json
{"error": "Invalid JSON format"}
{"error": "Image not found"}
{"error": "Endpoint not found"}
{"error": "Method not allowed"}
```

---

## CORS Support

All endpoints support CORS requests. The following headers are included in responses:

```
Access-Control-Allow-Origin: *
Access-Control-Allow-Methods: GET, POST, DELETE, OPTIONS
Access-Control-Allow-Headers: Content-Type
```

This allows the frontend to make requests from different origins.

---

## Example Usage

### Using JavaScript Fetch

**Get all images:**
```javascript
fetch('http://localhost:8080/api/images')
  .then(response => response.json())
  .then(data => console.log(data.images));
```

**Add new image:**
```javascript
fetch('http://localhost:8080/api/images', {
  method: 'POST',
  headers: { 'Content-Type': 'application/json' },
  body: JSON.stringify({
    id: 4,
    filename: 'mountain.jpg',
    width: 3840,
    height: 2160,
    size_kb: 1200,
    bit_depth: 24
  })
})
.then(response => response.json())
.then(data => console.log(data));
```

**Search image:**
```javascript
fetch('http://localhost:8080/api/search?id=2')
  .then(response => response.json())
  .then(data => {
    if (data.found) {
      console.log(data.image);
    } else {
      console.log('Image not found');
    }
  });
```

**Delete image:**
```javascript
fetch('http://localhost:8080/api/images?id=2', {
  method: 'DELETE'
})
.then(response => response.json())
.then(data => console.log(data.message));
```

**Sort images:**
```javascript
fetch('http://localhost:8080/api/sort?type=4')
  .then(response => response.json())
  .then(data => console.log(data.message));
```

### Using curl

**Get all images:**
```bash
curl http://localhost:8080/api/images | jq
```

**Add image:**
```bash
curl -X POST http://localhost:8080/api/images \
  -H "Content-Type: application/json" \
  -d '{"id":5,"filename":"ocean.jpg","width":2048,"height":1536,"size_kb":600,"bit_depth":24}' | jq
```

**Search:**
```bash
curl http://localhost:8080/api/search?id=1 | jq
```

**Delete:**
```bash
curl -X DELETE http://localhost:8080/api/images?id=3 | jq
```

**Sort:**
```bash
curl http://localhost:8080/api/sort?type=2 | jq
```

---

## Data Persistence

- All changes are automatically saved to `backend/data/images.csv`
- The CSV file is updated after:
  - Adding a new image (POST /images)
  - Deleting an image (DELETE /images)
  - Sorting images (GET /sort)
  
- On server restart, data is automatically loaded from the CSV file
