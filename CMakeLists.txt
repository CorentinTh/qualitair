# setup
cmake_minimum_required(VERSION 3.12)
project(qualitair)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -s -O3")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

# sources
set(SOURCES  src/main.cpp src/Test.cpp src/Test.h)

# targets
add_executable(qualitair ${SOURCES})

add_subdirectory(tests/unit-tests)
