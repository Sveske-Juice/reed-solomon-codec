cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(hamming VERSION 1.0)

# Include all source files
file(GLOB_RECURSE SRC_FILES src/*.cpp)
add_executable(hamming ${SRC_FILES})

# Include all headers
target_include_directories(hamming PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

