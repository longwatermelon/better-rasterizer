cmake_minimum_required(VERSION 3.20.5)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
project(rasterizer)

find_package(SDL2 CONFIG REQUIRED)

add_executable(rasterizer
    src/main.cpp
    src/rasterizer.h
    src/rasterizer.cpp
    src/file.h
    src/file.cpp
    src/common.h
    src/object.h
    src/object.cpp
    src/graphics.h
    src/graphics.cpp
    src/camera.h
    src/camera.cpp
)

target_link_libraries(rasterizer PRIVATE
    SDL2::SDL2 SDL2::SDL2main
)

