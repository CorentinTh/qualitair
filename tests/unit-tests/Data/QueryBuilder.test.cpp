//
// Created by vwallyn on 18/02/19.
//

#include <catch2/catch.hpp>
#include <SQLiteCpp/Statement.h>
#include <SQLiteCpp/Column.h>
#include "../../../src/Data/include/QueryBuilder.h"

TEST_CASE("Test query attribute selection", "[UT-D-2]") {
    QueryBuilder queryBuilder = QueryBuilder();

    REQUIRE(queryBuilder.getQuery() == "SELECT * FROM unknowTable;");

    queryBuilder.select("attributeId");
    REQUIRE(queryBuilder.getQuery() == "SELECT attributeId FROM unknowTable;");
}

TEST_CASE("Test query table selection", "[UT-D-3]") {
    QueryBuilder queryBuilder = QueryBuilder();

    queryBuilder.from("Measurement");
    REQUIRE(queryBuilder.getQuery() == "SELECT * FROM Measurement;");
}

TEST_CASE("Test query where condition", "[UT-D-4]") {
    QueryBuilder queryBuilder = QueryBuilder();

    queryBuilder.where("id = 12");
    REQUIRE(queryBuilder.getQuery() == "SELECT * FROM unknowTable WHERE id = 12;");
}

TEST_CASE("Test query andWhere condition", "[UT-D-5]") {
    QueryBuilder queryBuilder = QueryBuilder();

    queryBuilder.andWhere("id = 12");
    REQUIRE(queryBuilder.getQuery() == "SELECT * FROM unknowTable WHERE id = 12;");

    queryBuilder.andWhere("label = `helloWorld`");
    REQUIRE(queryBuilder.getQuery() == "SELECT * FROM unknowTable WHERE id = 12 AND label = `helloWorld`;");

    queryBuilder.andWhere("value != 16");
    REQUIRE(queryBuilder.getQuery() == "SELECT * FROM unknowTable WHERE id = 12 AND label = `helloWorld` AND value != 16;");
}

TEST_CASE("Test query orWhere condition", "[UT-D-6]") {
    QueryBuilder queryBuilder = QueryBuilder();

    queryBuilder.orWhere("id = 12");
    REQUIRE(queryBuilder.getQuery() == "SELECT * FROM unknowTable WHERE id = 12;");

    queryBuilder.orWhere("label = `helloWorld`");
    REQUIRE(queryBuilder.getQuery() == "SELECT * FROM unknowTable WHERE id = 12 OR label = `helloWorld`;");

    queryBuilder.orWhere("value != 16");
    REQUIRE(queryBuilder.getQuery() == "SELECT * FROM unknowTable WHERE id = 12 OR label = `helloWorld` OR value != 16;");
}

TEST_CASE("Test query join condition", "[UT-D-7]") {
    QueryBuilder queryBuilder = QueryBuilder();

    queryBuilder.join("Sensor");
    REQUIRE(queryBuilder.getQuery() == "SELECT * FROM unknowTable CROSS JOIN Sensor");
}

TEST_CASE("Test combined query", "[UT-D-8]") {
    QueryBuilder queryBuilder = QueryBuilder();

    queryBuilder.select("attributeId")
                .from("Attribute")
                .where("unit = `mg/l`")
                .orWhere("unit = `mol`");

    REQUIRE(queryBuilder.getQuery() == "SELECT attributeId FROM Attribute WHERE unit = `mg/l` OR unit = `mol`;");

    queryBuilder = QueryBuilder();
    queryBuilder.from("Measurment")
                .join("Attribute")
                .where("sensorId = 12");

    REQUIRE(queryBuilder.getQuery() == "SELECT * FROM Measurement CROSS JOIN Attribute WHERE sensorId = 12;");
}

TEST_CASE("Test QueryBuilder::execute", "[UT-D-9]") {
    QueryBuilder queryBuilder = QueryBuilder();
    SQLite::Statement * query = nullptr;

    query = queryBuilder.select("sensorId")
                        .from("Sensor")
                        .where("latitude < 48")
                        .execute();

    for(int i = 1; i <= 4; i++) {
        REQUIRE(query->executeStep());
        REQUIRE((int) query->getColumn("sensorId") == i);
    }

    queryBuilder = QueryBuilder();
    query = queryBuilder.from("Measurement")
                        .where("value < 6")
                        .andWhere("attributeId = 2")
                        .orWhere("sensorId = 5")
                        .execute();

    REQUIRE(query->executeStep());
    REQUIRE((int) query->getColumn("__rowid__") == 1);

    REQUIRE(query->executeStep());
    REQUIRE((int) query->getColumn("__rowid__") == 6);

    queryBuilder = QueryBuilder();
    query = queryBuilder.from("Attribute")
                        .join("Sensor")
                        .execute();

    int nbRows = 0;
    while(query->executeStep()) {
        nbRows++;
    }

    REQUIRE(nbRows == 15);
}
