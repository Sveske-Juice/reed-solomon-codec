cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

SET(CMAKE_C_FLAGS_DEBUG "-Wall -Wextra -Wunreachable-code -g -m32 -D_DEBUG -O0")

project(rsc VERSION 1.0)

# Include all source files
file(GLOB_RECURSE SRC_FILES src/*.cpp)
add_executable(rsc main.cpp ${SRC_FILES})

# Include all headers
target_include_directories(rsc PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_subdirectory(tests)

