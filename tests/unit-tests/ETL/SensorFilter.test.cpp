#include "catch2/catch.hpp"
#include <vector>
#include "../../../src/ETL/include/SensorFilter.h"
#include "../../../src/Data/include/ConnectionFactory.h"

using namespace std;

TEST_CASE("Testing SensorFilter::addSensor", "[UT-E-10]") {
    SQLite::Database * database = ConnectionFactory::getConnection();
    ConnectionFactory::setDatabase("../tests/data/dbmock.sqlite");
    QueryBuilder queryBuilder = QueryBuilder();
    queryBuilder.select("AttributeID").from("Measurement");

    SQLite::Statement * query;

    SensorFilter sensorFilter1;
    sensorFilter1.addSensor("1");
    sensorFilter1.addSensor("1");
    sensorFilter1.addSensor("");
    sensorFilter1.applyTo(queryBuilder);

    REQUIRE_NOTHROW(query = queryBuilder.execute());

    vector<int> vectResults;
    vectResults.push_back(1);
    vectResults.push_back(2);

    bool resultNotEmpty = false;

    while (query->executeStep()){
        resultNotEmpty = true;
        int attributeId = query->getColumn("AttributeID");
        REQUIRE(std::find(vectResults.begin(), vectResults.end(), attributeId) != vectResults.end());
        REQUIRE_THROWS(query->getColumn("inexistantColumn"));
    }

    REQUIRE(resultNotEmpty);
}

TEST_CASE("Testing SensorFilter::addSensors", "[UT-E-11]") {
    SQLite::Database * database = ConnectionFactory::getConnection();
    ConnectionFactory::setDatabase("../tests/data/dbmock.sqlite");
    QueryBuilder queryBuilder = QueryBuilder();
    queryBuilder.select("AttributeID").from("Measurement");

    SQLite::Statement * query;

    vector<string> attributes;
    attributes.emplace_back("2");
    attributes.emplace_back("2");
    attributes.emplace_back("4");
    attributes.emplace_back("5");
    attributes.emplace_back("");

    SensorFilter sensorFilter1;
    sensorFilter1.addSensors(attributes);
    sensorFilter1.applyTo(queryBuilder);

    REQUIRE_NOTHROW(query = queryBuilder.execute());

    int result = 3;

    bool resultNotEmpty = false;

    while (query->executeStep()){
        resultNotEmpty = true;
        int attributeId = query->getColumn("AttributeID");
        REQUIRE(result == attributeId);
        REQUIRE_THROWS(query->getColumn("inexistantColumn"));
    }

    REQUIRE(resultNotEmpty);
}

