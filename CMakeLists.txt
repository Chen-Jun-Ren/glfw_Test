cmake_minimum_required(VERSION 3.12)

project(glfw-example)
set(targetExec "glfw-example")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#SET(CMAKE_BUILD_TYPE "Debug")
SET(CMAKE_BUILD_TYPE "Release")

find_package(OpenGL REQUIRED)
find_package(glfw3 3.3 REQUIRED)
find_package(imgui REQUIRED)
find_package(glm CONFIG REQUIRED)
add_subdirectory(ext/glad)
include_directories(ext/glad/include)

add_executable(${targetExec} main.cpp "Shader/shader.h" "ext/stb_image/stb_image.cpp" "ext/root_directory.h")

target_link_libraries(${targetExec} glfw glad)
target_link_libraries(${targetExec} imgui::imgui)
target_link_libraries(${targetExec} glm::glm)

if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    target_link_libraries(${targetExec} OpenGL::OpenGL)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    target_link_libraries(${targetExec} OpenGL32)
endif()

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_link_libraries(${targetExec} dl)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
endif()

include(CPackConfig.cmake)
