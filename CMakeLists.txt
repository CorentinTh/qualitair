# pluggins
include(FetchContent)

# setup
cmake_minimum_required(VERSION 3.12)
project(qualitair)

set(TARGET_NAME qualitair)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -s -O3")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

# sources
file(GLOB SOURCES
        ${PROJECT_SOURCE_DIR}/src/**/*.h
        ${PROJECT_SOURCE_DIR}/src/**/*.cpp
        ${PROJECT_SOURCE_DIR}/src/main.cpp
)

set(EASYLOGGIN ${PROJECT_SOURCE_DIR}/deps/easyloggin/easylogging++.cc ${PROJECT_SOURCE_DIR}/deps/easyloggin/easylogging++.h)

# dependencies
FetchContent_Declare(
        sqlitecpp
        GIT_REPOSITORY https://github.com/SRombauts/SQLiteCpp.git
        GIT_TAG 2.2.0
)

FetchContent_Declare(
        jsoncpp
        GIT_REPOSITORY https://github.com/nlohmann/json.git
        GIT_TAG v3.5.0
)

FetchContent_GetProperties(sqlitecpp)
if (NOT sqlitecpp_POPULATED)
    FetchContent_Populate(sqlitecpp)
    add_subdirectory(${sqlitecpp_SOURCE_DIR} ${sqlitecpp_BINARY_DIR})
endif ()

FetchContent_GetProperties(jsoncpp)
if (NOT jsoncpp_POPULATED)
    FetchContent_Populate(jsoncpp)
    add_subdirectory(${jsoncpp_SOURCE_DIR} ${jsoncpp_BINARY_DIR})
endif ()

# targets
add_executable(${TARGET_NAME} ${SOURCES} ${EASYLOGGIN})

add_subdirectory(tests/unit-tests)

target_link_libraries(${TARGET_NAME}
        SQLiteCpp                       # sqlite
        sqlite3                         # sqlite dep
        pthread                         # sqlite dep
        dl                              # sqlite dep
        nlohmann_json::nlohmann_json    # json
)

target_include_directories(qualitair PRIVATE
        ${PROJECT_SOURCE_DIR}/deps/argh
        ${PROJECT_SOURCE_DIR}/deps/csvmonkey
        ${PROJECT_SOURCE_DIR}/deps/easyloggin
        ${PROJECT_SOURCE_DIR}/deps/inih
)