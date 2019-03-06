#include "catch2/catch.hpp"
#include "../../../src/ETL/include/ETL.h"

#include "nlohmann/json.hpp"

using json = nlohmann::json;
using namespace std;

//TODO ETL::getData()
//TODO write real tests

TEST_CASE("Testing ETL::ingest clean data", "[UT-E-1]") {
    ETL etl = ETL::getInstance();

    CHECK(etl.ingest("../data/csv/clean"));
}

TEST_CASE("Testing ETL::ingest not well formed csv", "[UT-E-1]") {
    ETL etl = ETL::getInstance();


    REQUIRE_THROWS(etl.ingest("../data/csv/dirty"));
}

TEST_CASE("Testing ETL::ingest with no data", "[UT-E-1]") {
    ETL etl = ETL::getInstance();


    CHECK(etl.ingest("../data/csv"));
}


TEST_CASE("Testing ETL singleton", "[extra]") {
    REQUIRE(&ETL::getInstance() == &ETL::getInstance());

    REQUIRE(typeid(ETL::getInstance()).name() == "ETL");
}
