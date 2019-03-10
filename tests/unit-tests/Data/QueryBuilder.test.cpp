//
// Created by vwallyn on 18/02/19.
//

#include <catch2/catch.hpp>
#include <SQLiteCpp/Statement.h>
#include <SQLiteCpp/Column.h>
#include "../../../src/Data/include/QueryBuilder.h"
#include "../../../src/Data/include/ConnectionFactory.h"

namespace nsquerybuilder {
    struct testInit {
        testInit() {
            ConnectionFactory::setDatabase("../tests/data/dbmock.sqlite");
        }
    } testInitInstance;

    TEST_CASE("Test query attribute selection", "[UT-D-2]") {
        QueryBuilder queryBuilder;

        REQUIRE(queryBuilder.getQuery() == "SELECT * FROM unknowTable;");

        queryBuilder.select("AttributeID");
        REQUIRE(queryBuilder.getQuery() == "SELECT AttributeID FROM unknowTable;");
    }

    TEST_CASE("Test query table selection", "[UT-D-3]") {
        QueryBuilder queryBuilder;

        queryBuilder.from("Measurement");
        REQUIRE(queryBuilder.getQuery() == "SELECT * FROM Measurement;");
    }

    TEST_CASE("Test query where condition", "[UT-D-4]") {
        QueryBuilder queryBuilder;

        queryBuilder.where("id = ?");
        REQUIRE(queryBuilder.getQuery() == "SELECT * FROM unknowTable WHERE id = ?;");
    }

    TEST_CASE("Test query andWhere condition", "[UT-D-5]") {
        QueryBuilder queryBuilder;

        queryBuilder.andWhere("id = ?");
        REQUIRE(queryBuilder.getQuery() == "SELECT * FROM unknowTable WHERE id = ?;");

        queryBuilder.andWhere("label = ?");
        REQUIRE(queryBuilder.getQuery() == "SELECT * FROM unknowTable WHERE id = ? AND label = ?;");

        queryBuilder.andWhere("Value != ?");
        REQUIRE(queryBuilder.getQuery() == "SELECT * FROM unknowTable WHERE id = ? AND label = ? AND Value != ?;");
    }

    TEST_CASE("Test query orWhere condition", "[UT-D-6]") {
        QueryBuilder queryBuilder;

        queryBuilder.orWhere("id = ?");
        REQUIRE(queryBuilder.getQuery() == "SELECT * FROM unknowTable WHERE id = ?;");

        queryBuilder.orWhere("label = ?");
        REQUIRE(queryBuilder.getQuery() == "SELECT * FROM unknowTable WHERE id = ? OR label = ?;");

        queryBuilder.orWhere("Value != ?");
        REQUIRE(queryBuilder.getQuery() == "SELECT * FROM unknowTable WHERE id = ? OR label = ? OR Value != ?;");
    }

    TEST_CASE("Test query join condition", "[UT-D-7]") {
        QueryBuilder queryBuilder;

        queryBuilder.join("Sensor");
        REQUIRE(queryBuilder.getQuery() == "SELECT * FROM unknowTable CROSS JOIN Sensor;");
    }

    TEST_CASE("Test combined query", "[UT-D-8]") {
        QueryBuilder queryBuilder;

        queryBuilder.select("AttributeID")
                    .from("Attribute")
                    .where("Unit = ?")
                    .orWhere("Unit = ?");

        REQUIRE(queryBuilder.getQuery() == "SELECT AttributeID FROM Attribute WHERE Unit = ? OR Unit = ?;");

        queryBuilder = QueryBuilder();
        queryBuilder.from("Measurement")
                    .join("Attribute")
                    .where("SensorID = ?");

        REQUIRE(queryBuilder.getQuery() == "SELECT * FROM Measurement CROSS JOIN Attribute WHERE SensorID = ?;");
    }

    TEST_CASE("Test insert", "[UT-D-9]") {
        QueryBuilder queryBuilder;

        queryBuilder.insert("Attribute")
                    .values({"AttributeID", "Unit", "Description"})
                    .bind("dummy").bind("dummy").bind("dummy");

        REQUIRE(queryBuilder.getQuery() == "INSERT INTO Attribute(AttributeID, Unit, Description) VALUES (?, ?, ?);");

        queryBuilder = QueryBuilder();
        queryBuilder = queryBuilder.insert("Sensor")
                .values({"SensorID", "Latitude", "Longitude", "Description"})
                .bind("dummy").bind("dummy").bind("dummy").bind("dummy")
                .bind("dummy").bind("dummy").bind("dummy").bind("dummy")
                .bind("dummy").bind("dummy").bind("dummy").bind("dummy");

        REQUIRE(queryBuilder.getQuery() == "INSERT INTO Sensor(SensorID, Latitude, Longitude, Description) VALUES (?, ?, ?, ?);");
    }

    TEST_CASE("Test QueryBuilder::execute", "[UT-D-10]") {
        QueryBuilder queryBuilder;
        SQLite::Statement * query;

        query = queryBuilder.select("SensorID")
                            .from("Sensor")
                            .where("Latitude < ?")
                            .bind(48.0)
                            .orderBy("SensorID")
                            .execute();

        for(int i = 1; i <= 4; i++) {
            REQUIRE(query->executeStep());
            REQUIRE(std::stoi(query->getColumn("SensorID")) == i);
        }

        queryBuilder = QueryBuilder();
        query = queryBuilder.select("rowid, *")
                            .from("Measurement")
                            .where("Value < ?")
                            .andWhere("AttributeID = ?")
                            .orWhere("SensorID = ?")
                            .bind(6)
                            .bind(2)
                            .bind(5)
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
}