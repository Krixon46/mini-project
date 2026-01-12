# 🧪 API Examples & Testing Guide

## Complete Usage Examples

### Using curl (Command Line)

#### 1. Check Backend is Running

```bash
curl http://localhost:8080/api/images
```

**Response:**
```json
{
  "images": [
    {
      "id": 67,
      "filename": "abc_03",
      "width": 56,
      "height": 99,
      "size_kb": 57.00,
      "bit_depth": 77
    },
    {
      "id": 1,
      "filename": "abc_01",
      "width": 45,
      "height": 56,
      "size_kb": 58.00,
      "bit_depth": 78
    }
  ]
}
```

---

#### 2. Add a New Image

```bash
curl -X POST http://localhost:8080/api/images \
  -H "Content-Type: application/json" \
  -d '{
    "id": 100,
    "filename": "vacation.jpg",
    "width": 3840,
    "height": 2160,
    "size_kb": 1500.75,
    "bit_depth": 24
  }'
```

**Response:**
```json
{
  "success": true,
  "message": "Image added",
  "id": 100
}
```

---

#### 3. Get All Images (Pretty Print)

```bash
curl http://localhost:8080/api/images | python3 -m json.tool
```

---

#### 4. Search for Image by ID

```bash
curl http://localhost:8080/api/search?id=1
```

**Response (Found):**
```json
{
  "found": true,
  "image": {
    "id": 1,
    "filename": "abc_01",
    "width": 45,
    "height": 56,
    "size_kb": 58.00,
    "bit_depth": 78
  }
}
```

**Response (Not Found):**
```json
{
  "found": false
}
```

---

#### 5. Delete Image

```bash
curl -X DELETE http://localhost:8080/api/images?id=100
```

**Response:**
```json
{
  "success": true,
  "message": "Image deleted"
}
```

---

#### 6. Sort Images

```bash
# Sort by ID
curl http://localhost:8080/api/sort?type=1

# Sort by Filename
curl http://localhost:8080/api/sort?type=2

# Sort by Width
curl http://localhost:8080/api/sort?type=3

# Sort by Height
curl http://localhost:8080/api/sort?type=4

# Sort by Size
curl http://localhost:8080/api/sort?type=5

# Sort by Bit Depth
curl http://localhost:8080/api/sort?type=6
```

**Response:**
```json
{
  "success": true,
  "message": "Images sorted"
}
```

---

#### 7. Reload CSV

```bash
curl http://localhost:8080/api/load
```

**Response:**
```json
{
  "success": true,
  "message": "CSV loaded",
  "count": 3
}
```

---

## Using JavaScript (Frontend)

### 1. Get All Images

```javascript
fetch('http://localhost:8080/api/images')
  .then(response => response.json())
  .then(data => {
    console.log('Images:', data.images);
    data.images.forEach(img => {
      console.log(`${img.id}: ${img.filename} (${img.width}x${img.height})`);
    });
  })
  .catch(error => console.error('Error:', error));
```

---

### 2. Add New Image

```javascript
const newImage = {
  id: 101,
  filename: "sunset.jpg",
  width: 2560,
  height: 1440,
  size_kb: 800.50,
  bit_depth: 24
};

fetch('http://localhost:8080/api/images', {
  method: 'POST',
  headers: {
    'Content-Type': 'application/json'
  },
  body: JSON.stringify(newImage)
})
.then(response => response.json())
.then(data => {
  if (data.success) {
    console.log('Image added with ID:', data.id);
  } else {
    console.error('Error:', data.error);
  }
})
.catch(error => console.error('Error:', error));
```

---

### 3. Search Image

```javascript
const searchId = 1;

fetch(`http://localhost:8080/api/search?id=${searchId}`)
  .then(response => response.json())
  .then(data => {
    if (data.found) {
      const img = data.image;
      console.log(`Found: ${img.filename}`);
      console.log(`Dimensions: ${img.width}x${img.height}`);
      console.log(`Size: ${img.size_kb}KB`);
      console.log(`Bit Depth: ${img.bit_depth}-bit`);
    } else {
      console.log('Image not found');
    }
  })
  .catch(error => console.error('Error:', error));
```

---

### 4. Delete Image

```javascript
const imageId = 101;

fetch(`http://localhost:8080/api/images?id=${imageId}`, {
  method: 'DELETE'
})
.then(response => response.json())
.then(data => {
  if (data.success) {
    console.log('Image deleted successfully');
  } else {
    console.error('Error:', data.error);
  }
})
.catch(error => console.error('Error:', error));
```

---

### 5. Sort Images

```javascript
const sortType = 4; // Sort by height

fetch(`http://localhost:8080/api/sort?type=${sortType}`)
  .then(response => response.json())
  .then(data => {
    if (data.success) {
      console.log('Images sorted by height');
    }
  })
  .catch(error => console.error('Error:', error));
```

---

### 6. Get Count of Images

```javascript
fetch('http://localhost:8080/api/images')
  .then(response => response.json())
  .then(data => {
    const count = data.images.length;
    const totalSize = data.images.reduce((sum, img) => sum + img.size_kb, 0);
    
    console.log(`Total Images: ${count}`);
    console.log(`Total Size: ${totalSize.toFixed(2)}KB`);
    console.log(`Average Size: ${(totalSize / count).toFixed(2)}KB`);
  })
  .catch(error => console.error('Error:', error));
```

---

## Using Python (requests library)

### Setup

```bash
pip install requests
```

### 1. Get All Images

```python
import requests

response = requests.get('http://localhost:8080/api/images')
data = response.json()

for img in data['images']:
    print(f"ID: {img['id']}, Filename: {img['filename']}, "
          f"Resolution: {img['width']}x{img['height']}")
```

---

### 2. Add Image

```python
import requests

new_image = {
    'id': 102,
    'filename': 'mountain.jpg',
    'width': 4096,
    'height': 2304,
    'size_kb': 1200.50,
    'bit_depth': 24
}

response = requests.post('http://localhost:8080/api/images', json=new_image)
data = response.json()

if data['success']:
    print(f"Image added with ID: {data['id']}")
else:
    print(f"Error: {data['error']}")
```

---

### 3. Search Image

```python
import requests

image_id = 1
response = requests.get(f'http://localhost:8080/api/search?id={image_id}')
data = response.json()

if data['found']:
    img = data['image']
    print(f"Found: {img['filename']}")
    print(f"Dimensions: {img['width']}x{img['height']}")
else:
    print("Image not found")
```

---

### 4. Delete Image

```python
import requests

image_id = 102
response = requests.delete(f'http://localhost:8080/api/images?id={image_id}')
data = response.json()

if data['success']:
    print("Image deleted")
else:
    print(f"Error: {data['error']}")
```

---

### 5. Sort Images

```python
import requests

# 1=ID, 2=Filename, 3=Width, 4=Height, 5=Size, 6=Bit Depth
sort_type = 4  # Sort by height

response = requests.get(f'http://localhost:8080/api/sort?type={sort_type}')
data = response.json()

if data['success']:
    print("Images sorted by height")
```

---

## Complete Test Sequence

Run these commands in order to test everything:

```bash
# 1. Check initial state
curl http://localhost:8080/api/images

# 2. Add new image
curl -X POST http://localhost:8080/api/images \
  -H "Content-Type: application/json" \
  -d '{
    "id": 999,
    "filename": "test.jpg",
    "width": 1024,
    "height": 768,
    "size_kb": 200.5,
    "bit_depth": 24
  }'

# 3. Verify it was added
curl http://localhost:8080/api/images | python3 -m json.tool

# 4. Search for it
curl http://localhost:8080/api/search?id=999

# 5. Sort by height
curl http://localhost:8080/api/sort?type=4

# 6. Verify sort
curl http://localhost:8080/api/images | python3 -m json.tool

# 7. Delete the test image
curl -X DELETE http://localhost:8080/api/images?id=999

# 8. Verify deletion
curl http://localhost:8080/api/images | python3 -m json.tool
```

---

## Error Responses

### Bad Request (400)

```json
{
  "error": "Invalid JSON format"
}
```

### Not Found (404)

```json
{
  "found": false
}
```

### Method Not Allowed (405)

```json
{
  "error": "Method not allowed"
}
```

### Endpoint Not Found (400)

```json
{
  "error": "Endpoint not found"
}
```

---

## Tips for Testing

### Using jq for Pretty JSON

```bash
# Install jq
sudo apt-get install jq

# Use with curl
curl http://localhost:8080/api/images | jq

# Pretty print with specific fields
curl http://localhost:8080/api/images | jq '.images[] | {id, filename, size_kb}'
```

### Batch Operations

```bash
# Add multiple images
for i in {1..5}; do
  curl -X POST http://localhost:8080/api/images \
    -H "Content-Type: application/json" \
    -d "{\"id\": $i, \"filename\": \"image$i.jpg\", \"width\": $((i * 100)), \"height\": $((i * 100)), \"size_kb\": $((i * 50)), \"bit_depth\": 24}"
done
```

### Monitor Changes

```bash
# Watch for changes
watch curl http://localhost:8080/api/images

# Or use python to monitor
python3 -c "
import requests, time
while True:
    data = requests.get('http://localhost:8080/api/images').json()
    print(f'Total images: {len(data[\"images\"])}')
    time.sleep(2)
"
```

---

## Performance Notes

- Each request is handled in a separate thread
- Thread-safe with mutex locks
- CSV is updated after write operations
- No database overhead
- Suitable for small to medium datasets

---

## CORS Details

All responses include these headers:
```
Access-Control-Allow-Origin: *
Access-Control-Allow-Methods: GET, POST, DELETE, OPTIONS
Access-Control-Allow-Headers: Content-Type
```

This allows requests from any origin on any port.

---

## Integration Examples

### React Component

```javascript
const [images, setImages] = useState([]);
const [loading, setLoading] = useState(true);

useEffect(() => {
  fetch('http://localhost:8080/api/images')
    .then(res => res.json())
    .then(data => {
      setImages(data.images);
      setLoading(false);
    });
}, []);

if (loading) return <div>Loading...</div>;

return (
  <div>
    {images.map(img => (
      <div key={img.id}>
        <h3>{img.filename}</h3>
        <p>{img.width}x{img.height}</p>
      </div>
    ))}
  </div>
);
```

### Vue.js

```javascript
<template>
  <div>
    <img-list v-bind:images="images" />
  </div>
</template>

<script>
export default {
  data() {
    return {
      images: []
    }
  },
  mounted() {
    fetch('http://localhost:8080/api/images')
      .then(res => res.json())
      .then(data => this.images = data.images)
  }
}
</script>
```

---

## Next Steps

Now that you know the API:
1. Build custom clients
2. Create mobile apps
3. Build desktop applications
4. Integrate with other services
5. Create analytics dashboards
