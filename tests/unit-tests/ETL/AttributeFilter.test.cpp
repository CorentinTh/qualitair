//
//        ----[  QUALIT'AIR  ]----
//
//    Marsaud Menseau Thomasset Wallyn
//  Copyright © 2019 - All right reserved
//

#include "catch2/catch.hpp"
#include <string>
#include <vector>
#include <SQLiteCpp/Database.h>
#include "../../../src/Data/include/ConnectionFactory.h"
#include "../../../src/ETL/include/AttributeFilter.h"
#include "../../../src/Data/include/QueryBuilder.h"


using namespace std;

TEST_CASE("Testing AttributeFilter::addAttribute", "[UT-E-8]") {
    SQLite::Database *database = ConnectionFactory::getConnection();
    ConnectionFactory::setDatabase("../tests/data/dbmock.sqlite");
    QueryBuilder queryBuilder = QueryBuilder();

    SQLite::Statement *query;

    queryBuilder.select("SensorID")
            .from("Measurement")
            .join("Attribute")
            .where("Measurement.AttributeID = Attribute.AttributeID");

    AttributeFilter attributeFilter1;
    attributeFilter1.addAttribute("3");
    attributeFilter1.addAttribute("3");
    attributeFilter1.addAttribute("");
    attributeFilter1.applyTo(queryBuilder);

    CHECK_NOTHROW(query = queryBuilder.execute());

    vector<int> vectSensorId;
    vectSensorId.push_back(2);
    vectSensorId.push_back(4);
    vectSensorId.push_back(5);

    bool resultNotEmpty = false;

    while (query->executeStep()) {
        resultNotEmpty = true;
        int sensorId = query->getColumn("SensorID");
        CHECK(std::find(vectSensorId.begin(), vectSensorId.end(), sensorId) != vectSensorId.end());
        CHECK_THROWS(query->getColumn("inexistantColumn"));
    }

    CHECK(resultNotEmpty);
}

TEST_CASE("Testing AttributeFilter::addAttributes", "[UT-E-9]") {
    SQLite::Database *database = ConnectionFactory::getConnection();
    ConnectionFactory::setDatabase("../tests/data/dbmock.sqlite");
    QueryBuilder queryBuilder = QueryBuilder();
    queryBuilder.select("SensorID")
            .from("Measurement")
            .join("Attribute")
            .where("Measurement.AttributeID = Attribute.AttributeID");

    SQLite::Statement *query;

    vector<string> attributes;
    attributes.emplace_back("1");
    attributes.emplace_back("2");
    attributes.emplace_back("3");
    attributes.emplace_back("");

    AttributeFilter attributeFilter2;
    attributeFilter2.addAttributes(attributes);
    attributeFilter2.applyTo(queryBuilder);

    CHECK_NOTHROW(query = queryBuilder.execute());

    vector<int> vectResults;
    vectResults.push_back(1);
    vectResults.push_back(2);
    vectResults.push_back(4);
    vectResults.push_back(5);

    bool resultNotEmpty = false;

    while (query->executeStep()) {
        resultNotEmpty = true;
        int sensorId = query->getColumn("SensorID");
        CHECK(std::find(vectResults.begin(), vectResults.end(), sensorId) != vectResults.end());
        CHECK_THROWS(query->getColumn("inexistantColumn"));
    }

    CHECK(resultNotEmpty);
}

