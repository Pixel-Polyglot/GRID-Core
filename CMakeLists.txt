cmake_minimum_required(VERSION 3.7)

project(GRID-Core LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 23)

set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_CXX_FLAGS "-Wall -Wextra")

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(CMAKE_CXX_FLAGS_RELEASE "-O3")
else()
    set(CMAKE_CXX_FLAGS_DEBUG "-g")
endif()

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

link_directories(deps/libs)
include_directories(deps/include src/headers deps/libs/imgui deps/libs/implot deps/include/TinyTIFF)
file(GLOB_RECURSE SOURCES src/*.cpp)

add_library(GRID-Core SHARED ${SOURCES})

set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)
if(OPENGL_FOUND)
    message("OpenGL found")
else()
    message(FATAL_ERROR "OpenGL not found")
endif()

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(deps/libs/GLFW)

add_subdirectory(deps/libs/TinyTIFF)

add_library(GLAD deps/include/glad/glad.c)

file(GLOB IMGUI_SOURCES
    deps/libs/imgui/*.cpp
    deps/libs/imgui/*.h
    deps/libs/imgui/backends/imgui_impl_glfw.cpp
    deps/libs/imgui/backends/imgui_impl_glfw.h
    deps/libs/imgui/backends/imgui_impl_opengl3.cpp
    deps/libs/imgui/backends/imgui_impl_opengl3.h)
    
add_library(ImGUI ${IMGUI_SOURCES})

file(GLOB IMPLOT_SOURCES
    deps/libs/implot/*.cpp
    deps/libs/implot/*.h)

add_library(ImPLOT ${IMPLOT_SOURCES})

set(LIBS glfw GLAD ImGUI ImPLOT ${OPENGL_LIBRARY} TinyTIFF::TinyTIFF)

target_link_libraries(GRID-Core ${LIBS} -static-libgcc -static-libstdc++)