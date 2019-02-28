//
// Created by vwallyn on 18/02/19.
//

#include <catch2/catch.hpp>
#include <SQLiteCpp/Statement.h>
#include <SQLiteCpp/Column.h>
#include "../../../src/Data/include/QueryBuilder.h"
#include "../../../src/Data/include/ConnectionFactory.h"

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

    queryBuilder.where("id = ?");
    REQUIRE(queryBuilder.getQuery() == "SELECT * FROM unknowTable WHERE id = ?;");
}

TEST_CASE("Test query andWhere condition", "[UT-D-5]") {
    QueryBuilder queryBuilder = QueryBuilder();

    queryBuilder.andWhere("id = ?");
    REQUIRE(queryBuilder.getQuery() == "SELECT * FROM unknowTable WHERE id = ?;");

    queryBuilder.andWhere("label = ?");
    REQUIRE(queryBuilder.getQuery() == "SELECT * FROM unknowTable WHERE id = ? AND label = ?;");

    queryBuilder.andWhere("value != ?");
    REQUIRE(queryBuilder.getQuery() == "SELECT * FROM unknowTable WHERE id = ? AND label = ? AND value != ?;");
}

TEST_CASE("Test query orWhere condition", "[UT-D-6]") {
    QueryBuilder queryBuilder = QueryBuilder();

    queryBuilder.orWhere("id = ?");
    REQUIRE(queryBuilder.getQuery() == "SELECT * FROM unknowTable WHERE id = ?;");

    queryBuilder.orWhere("label = ?");
    REQUIRE(queryBuilder.getQuery() == "SELECT * FROM unknowTable WHERE id = ? OR label = ?;");

    queryBuilder.orWhere("value != ?");
    REQUIRE(queryBuilder.getQuery() == "SELECT * FROM unknowTable WHERE id = ? OR label = ? OR value != ?;");
}

TEST_CASE("Test query join condition", "[UT-D-7]") {
    QueryBuilder queryBuilder = QueryBuilder();

    queryBuilder.join("Sensor");
    REQUIRE(queryBuilder.getQuery() == "SELECT * FROM unknowTable CROSS JOIN Sensor;");
}

TEST_CASE("Test combined query", "[UT-D-8]") {
    QueryBuilder queryBuilder = QueryBuilder();

    queryBuilder.select("attributeId")
                .from("Attribute")
                .where("unit = ?")
                .orWhere("unit = ?");

    REQUIRE(queryBuilder.getQuery() == "SELECT attributeId FROM Attribute WHERE unit = ? OR unit = ?;");

    queryBuilder = QueryBuilder();
    queryBuilder.from("Measurement")
                .join("Attribute")
                .where("sensorId = ?");

    REQUIRE(queryBuilder.getQuery() == "SELECT * FROM Measurement CROSS JOIN Attribute WHERE sensorId = ?;");
}

TEST_CASE("Test QueryBuilder::execute", "[UT-D-9]") {
    ConnectionFactory::setDatabase("../tests/data/dbmock.sqlite");
    QueryBuilder queryBuilder = QueryBuilder();
    SQLite::Statement * query;

    query = queryBuilder.select("sensorId")
                        .from("Sensor")
                        .where("latitude < ?")
                        .bind(1, 48.0)
                        .execute();

    for(int i = 1; i <= 4; i++) {
        REQUIRE(query->executeStep());
        REQUIRE((int) query->getColumn("sensorId") == i);
    }

    queryBuilder = QueryBuilder();
    query = queryBuilder.select("rowid, *")
                        .from("Measurement")
                        .where("value < ?")
                        .andWhere("attributeId = ?")
                        .orWhere("sensorId = ?")
                        .bind(1, 6)
                        .bind(2, 2)
                        .bind(3, 5)
                        .execute();

    REQUIRE(query->executeStep());
    REQUIRE((int) query->getColumn("rowid") == 2);

    REQUIRE(query->executeStep());
    REQUIRE((int) query->getColumn("rowid") == 6);

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
