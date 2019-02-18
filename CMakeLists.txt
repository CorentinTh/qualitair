# pluggins
include(FetchContent)

# setup
cmake_minimum_required(VERSION 3.12)
project(qualitair)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -s -O3")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

# sources
set(SOURCES src/main.cpp src/Test.cpp src/Test.h src/View/src/OutputCLI.cpp src/View/include/OutputCLI.h src/View/src/OutputHTML.cpp src/View/include/OutputHTML.h src/View/src/OutputJSON.cpp src/View/include/OutputJSON.h src/View/src/IOutput.cpp src/View/include/IOutput.h src/ETL/src/IETL.cpp src/ETL/include/IETL.h src/ETL/src/ETL.cpp src/ETL/include/ETL.h src/ETL/src/Interpolater.cpp src/ETL/include/Interpolater.h src/ETL/src/Filter.cpp src/ETL/include/Filter.h src/ETL/src/TimeFilter.cpp src/ETL/include/TimeFilter.h src/ETL/src/AttributeFilter.cpp src/ETL/include/AttributeFilter.h src/ETL/src/GeoFilter.cpp src/ETL/include/GeoFilter.h src/ETL/src/SensorFilter.cpp src/ETL/include/SensorFilter.h src/ETL/src/Point.cpp src/ETL/include/Point.h src/DataProcessor/src/IDataProcessor.cpp src/DataProcessor/include/IDataProcessor.h src/DataProcessor/src/DataProcessor.cpp src/DataProcessor/include/DataProcessor.h src/DataProcessor/src/IDataProcess.cpp src/DataProcessor/include/IDataProcess.h src/DataProcessor/src/Aggregation.cpp src/DataProcessor/include/Aggregation.h src/DataProcessor/src/SpikeDetection.cpp src/DataProcessor/include/SpikeDetection.h src/DataProcessor/src/SimilarDetection.cpp src/DataProcessor/include/SimilarDetection.h src/DataProcessor/src/BrokenDetection.cpp src/DataProcessor/include/BrokenDetection.h src/DataProcessor/src/FormulaComputer.cpp src/DataProcessor/include/FormulaComputer.h src/Data/src/IData.cpp src/Data/include/IData.h src/Data/src/QueryBuilder.cpp src/Data/include/QueryBuilder.h src/Data/src/ConnectionFactory.cpp src/Data/include/ConnectionFactory.h src/Data/src/Sensor.cpp src/Data/include/Sensor.h src/Data/src/Measurement.cpp src/Data/include/Measurement.h src/Data/src/Attribute.cpp src/Data/include/Attribute.h src/Controller/src/Controller.cpp src/Controller/include/Controller.h src/Controller/src/CLIParser.cpp src/Controller/include/CLIParser.h src/Controller/src/Config.cpp src/Controller/include/Config.h src/Controller/src/Command.cpp src/Controller/include/Command.h src/Controller/src/SpikesCommand.cpp src/Controller/include/SpikesCommand.h src/Controller/src/StatsCommand.cpp src/Controller/include/StatsCommand.h src/Controller/src/DetectSimCommand.cpp src/Controller/include/DetectSimCommand.h src/Controller/src/DetectBrokenCommand.cpp src/Controller/include/DetectBrokenCommand.h src/Controller/src/IngestCommand.cpp src/Controller/include/IngestCommand.h src/globals.h)


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
add_executable(qualitair ${SOURCES})

add_subdirectory(tests/unit-tests)

target_link_libraries(qualitair
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