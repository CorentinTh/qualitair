# pluggins
include(FetchContent)

# sources
set(SOURCES_UTESTS Test.test.cpp ../../src/Test.cpp ../../src/Test.h DataProcessor/Aggregation.test.cpp DataProcessor/FormulaComputer.test.cpp DataProcessor/SpikeDetection.test.cpp DataProcessor/SimilarDetection.test.cpp DataProcessor/BrokenDetection.cpp DataProcessor/DataProcessor.test.cpp Controller/CLIParser.test.cpp Controller/Config.test.cpp View/OutputCLI.test.cpp View/OutputHTML.test.cpp View/OutputJSON.test.cpp Data/ConnectionFactory.test.cpp Data/QueryBuilder.test.cpp ETL/ETL.test.cpp ETL/TimeFilter.test.cpp ETL/GeoFilter.test.cpp ETL/AttributeFilter.test.cpp ETL/SensorFilter.test.cpp ETL/Interpolater.test.cpp)

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

if (ENABLE_COVERAGE)
    list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/CMake")
    find_package(codecov)
    add_coverage(SelfTest)
    list(APPEND LCOV_REMOVE_PATTERNS "/usr/")
    coverage_evaluate()
endif()


# targets
add_executable(utests ${SOURCES_UTESTS})

target_link_libraries(utests
        SQLiteCpp                       # sqlite
        sqlite3                         # sqlite dep
        pthread                         # sqlite dep
        dl                              # sqlite dep
        nlohmann_json::nlohmann_json    # json
)

target_link_libraries(utests Catch2::Catch2)
