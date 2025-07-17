cmake_minimum_required(VERSION 3.10)
project(MultiThreadedWebServer)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(WebServer
    src/main.cpp
    src/Server.cpp
    src/ThreadPool.cpp
    src/RequestHandler.cpp
)

target_link_libraries(WebServer pthread)
