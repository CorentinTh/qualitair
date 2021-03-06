# pluggins
include(FetchContent)

# config
set(TARGET_NAME utests)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 --coverage")


# sources
file(GLOB UT_SOURCES
        ${PROJECT_SOURCE_DIR}/tests/unit-tests/**/*.h
        ${PROJECT_SOURCE_DIR}/tests/unit-tests/**/*.cpp
        ${PROJECT_SOURCE_DIR}/tests/unit-tests/*.h
        ${PROJECT_SOURCE_DIR}/tests/unit-tests/*.cpp
)

list(APPEND SOURCES ${UT_SOURCES})

# dependencies
FetchContent_Declare(
        catch2
        GIT_REPOSITORY  https://github.com/catchorg/Catch2.git
        GIT_TAG         v2.6.1
)

FetchContent_Declare(
        sqlitecpp
        GIT_REPOSITORY https://github.com/SRombauts/SQLiteCpp.git
        GIT_TAG 2.2.0
)

FetchContent_GetProperties(catch2)
if(NOT catch2_POPULATED)
    FetchContent_Populate(catch2)
    add_subdirectory(${catch2_SOURCE_DIR} ${catch2_BINARY_DIR})
endif()

FetchContent_GetProperties(sqlitecpp)
if (NOT sqlitecpp_POPULATED)
    FetchContent_Populate(sqlitecpp)
    add_subdirectory(${sqlitecpp_SOURCE_DIR} ${sqlitecpp_BINARY_DIR})
endif ()

# targets
add_executable(${TARGET_NAME} ${SOURCES})

target_link_libraries(${TARGET_NAME} Catch2::Catch2 ${REMOTE_DEPS})

target_include_directories(${TARGET_NAME} PRIVATE ${LOCAL_DEPS})

