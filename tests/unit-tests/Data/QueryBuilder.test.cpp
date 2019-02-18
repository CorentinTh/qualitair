//
// Created by vwallyn on 18/02/19.
//

#include <catch2/catch.hpp>
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

    queryBuilder.select("attributeId");
    queryBuilder.from("Attribute");
    queryBuilder.where("unit = `mg/l`");
    queryBuilder.orWhere("unit = `mol`");

    REQUIRE(queryBuilder.getQuery() == "SELECT attributeId FROM Attribute WHERE unit = `mg/l` OR unit = `mol`;");

    queryBuilder = QueryBuilder();
    queryBuilder.from("Measurment");
    queryBuilder.join("Attribute");
    queryBuilder.where("sensorId = 12");

    REQUIRE(queryBuilder.getQuery() == "SELECT * FROM Measurement CROSS JOIN Attribute WHERE sensorId = 12;")
}
