#include <SQLiteCpp/Database.h>
#include <fstream>
#include "catch2/catch.hpp"
#include "../../../src/ETL/include/ETL.h"

#include "nlohmann/json.hpp"
#include "../../../src/Data/include/ConnectionFactory.h"

//TODO ETL::getData()

namespace etlTestNamespace {
    void copyFile(std::string source, std::string destination) {
        std::remove(destination.c_str());
        std::ifstream sourceStream(source, std::ios::binary);
        std::ofstream destinationStream(destination, std::ios::binary);

        destinationStream << sourceStream.rdbuf();

        sourceStream.close();
        destinationStream.close();
    }

    void initializeDatabase() {
        copyFile("../tests/data/dbmock.sqlite", "../tests/data/dbmockcopy.sqlite");
        ConnectionFactory::setDatabase("../tests/data/dbmockcopy.sqlite");
    }

    TEST_CASE("Testing ETL::ingest clean data", "[UT-E-1]") {
        initializeDatabase();
        ETL etl = ETL::getInstance();

        REQUIRE(etl.ingest("../tests/data/csv/clean") == 19);
    }

    TEST_CASE("Testing ETL::ingest not well formed csv", "[UT-E-1]") {
//        initializeDatabase();
        ETL etl = ETL::getInstance();

        REQUIRE(etl.ingest("../tests/data/csv/dirty") == -1);
    }

    TEST_CASE("Testing ETL::ingest with no data", "[UT-E-1]") {
//        initializeDatabase();
        ETL etl = ETL::getInstance();

        REQUIRE(etl.ingest("../data/csv") == 0);
    }


    TEST_CASE("Testing ETL singleton", "[extra]") {
        REQUIRE(&ETL::getInstance() == &ETL::getInstance());

        REQUIRE(typeid(ETL::getInstance()).name() == "ETL");
    }
}

