# Multithreaded Web Server (C++)

A simple multithreaded HTTP web server implemented in C++ using sockets and a thread pool.

## 📋 Features
- Handles multiple clients concurrently using thread pool.
- Supports HTTP GET requests.
- Serves static files (HTML).
- Basic logging of incoming requests.

---

## 🚀 Build Instructions

### 1 Prerequisites
- C++17 compiler (`g++` or `clang++`)
- CMake >= 3.10
- Unix/Linux/macOS environment

### 2 Build

```bash
git clone <your-repo-url>
cd WebServer
mkdir build
cd build
cmake ..
make
```

### 3 Run

```bash
cd build
cp -r ../static . 
./WebServer
```


