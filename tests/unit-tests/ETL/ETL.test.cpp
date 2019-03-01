#include "catch2/catch.hpp"
#include "../../../src/ETL/include/ETL.h"

#include "nlohmann/json.hpp"

using json = nlohmann::json;
using namespace std;

//TODO ETL::getData()

TEST_CASE("Testing ETL::ingest with clean measure data", "[UT-E-1]") {
    ETL etl = ETL::getInstance();

    CHECK(etl.ingest(
            {
                    {"type",        ETL::MEASURE},
                    {"Timestamp",   "10"},
                    {"SensorID",    "10"},
                    {"AttributeID", "10"},
                    {"Value",       "10"},
            }
    ));
}

TEST_CASE("Testing ETL::ingest with corrupted measure data", "[UT-E-1]") {
    ETL etl = ETL::getInstance();


    REQUIRE_THROWS(etl.ingest(
            {
                    {"type",            ETL::MEASURE},
                    {"Timestasqfqdgmp", "10"},
                    {"SensorqsdfID",    "10"},
                    {"AttribuqsdfteID", "10"},
                    {"qfds",            "10"},
            }
    ));
}

TEST_CASE("Testing ETL::ingest with clean attribute data", "[UT-E-1]") {
    ETL etl = ETL::getInstance();


    CHECK(etl.ingest(
            {
                    {"type",        ETL::ATTRIBUTE},
                    {"Unit",        "10"},
                    {"AttributeID", "10"},
                    {"Description", "10"},
            }
    ));
}

TEST_CASE("Testing ETL::ingest with corrupted attribute data", "[UT-E-1]") {
    ETL etl = ETL::getInstance();


    REQUIRE_THROWS(etl.ingest(
            {
                    {"type",           ETL::ATTRIBUTE},
                    {"Unisdft",        "10"},
                    {"AttrsdfibuteID", "10"},
                    {"Descsdfription", "10"},
            }
    ));
}

TEST_CASE("Testing ETL::ingest with clean sensor data", "[UT-E-1]") {
    ETL etl = ETL::getInstance();


    CHECK(etl.ingest(
            {
                    {"type",        ETL::ATTRIBUTE},
                    {"Longitude",   "10"},
                    {"Latitude",    "10"},
                    {"SensorID",    "10"},
                    {"Description", "10"},
            }
    ));
}

TEST_CASE("Testing ETL::ingest with corrupted sensor data", "[UT-E-1]") {
    ETL etl = ETL::getInstance();


    REQUIRE_THROWS(etl.ingest(
            {
                    {"type",           ETL::ATTRIBUTE},
                    {"Longiqsdtude",   "10"},
                    {"Latiqsdtude",    "10"},
                    {"SensqdsorID",    "10"},
                    {"Descqsdription", "10"},
            }
    ));
}

TEST_CASE("Testing ETL singleton", "[extra]") {
    REQUIRE(&ETL::getInstance() == &ETL::getInstance());

    REQUIRE(typeid(ETL::getInstance()).name() == "ETL");
}
