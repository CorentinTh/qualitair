#include "catch2/catch.hpp"
#include "../../../src/ETL/include/GeoFilter.h"
#include "../../../src/Data/include/ConnectionFactory.h"

using namespace std;

TEST_CASE("Testing GeoFilter::setBBox", "[UT-E-6]") {
    SECTION("with normal BBox"){
        SQLite::Database * database = ConnectionFactory::getConnection();
        ConnectionFactory::setDatabase("../tests/data/dbmock.sqlite");
        QueryBuilder queryBuilder = QueryBuilder();

        SQLite::Statement * query;

        queryBuilder.select("SensorID").from("Sensor");

        BBox b = {4.83, 50.54412, 4.84, 40.13849};

        GeoFilter geoFilter1;
        REQUIRE_NOTHROW(geoFilter1.setBBox(b));
        geoFilter1.applyTo(queryBuilder);

        REQUIRE_NOTHROW(query = queryBuilder.execute()); // to help debug

        vector<int> vectResult;
        vectResult.push_back(1);
        vectResult.push_back(2);
        vectResult.push_back(3);

        bool resultNotEmpty = false;

        while (query->executeStep()){
            resultNotEmpty = true;
            int sensorId = query->getColumn("SensorID");
            REQUIRE(std::find(vectResult.begin(), vectResult.end(), sensorId) != vectResult.end());
            REQUIRE_THROWS(query->getColumn("inexistantColumn"));
        }

        REQUIRE(resultNotEmpty);
    }

    SECTION("with bad BBox"){
        GeoFilter geoFilter1;

        BBox b1 = {10, 11, -20, 21}; // impossible : left >= right
        BBox b2 = {-181.54684, 147.05310, 49.21657, 0.15746}; // impossible : left < -180
        GeoFilter geoFilter2;
        REQUIRE_THROWS(geoFilter2.setBBox(b1));
        REQUIRE_THROWS(geoFilter2.setBBox(b2));
    }
}


TEST_CASE("Testing GeoFilter::extend", "[UT-E-7]") {

    SECTION("with and without extension with valElargissement=0.05"){
        SQLite::Database * database = ConnectionFactory::getConnection();
        ConnectionFactory::setDatabase("../tests/data/dbmock.sqlite");
        QueryBuilder queryBuilder = QueryBuilder();
        queryBuilder.select("SensorID").from("Sensor");

        SQLite::Statement * query;

        SECTION("without extension : no results are found"){

            GeoFilter geoFilter3;
            BBox b = {4.7, 50.54412, 4.8, 40.13849};
            REQUIRE_NOTHROW(geoFilter3.setBBox(b));
            geoFilter3.applyTo(queryBuilder);

            REQUIRE_NOTHROW(query = queryBuilder.execute()); // to help debug

            REQUIRE(!query->executeStep());
            // empty result
        }

        SECTION("extension of the bbox : results found"){
            GeoFilter geoFilter4;
            BBox b = {4.7, 50.54412, 4.8, 40.13849};
            REQUIRE_NOTHROW(geoFilter4.setBBox(b));
            REQUIRE_NOTHROW(geoFilter4.extend(0.05));
            geoFilter4.applyTo(queryBuilder);

            REQUIRE_NOTHROW(query = queryBuilder.execute()); // to help debug

            vector<int> vectResult;
            vectResult.push_back(1);
            vectResult.push_back(2);
            vectResult.push_back(3);

            bool resultNotEmpty = false;

            while (query->executeStep()){
                resultNotEmpty = true;
                int sensorId = query->getColumn("SensorID");
                REQUIRE(std::find(vectResult.begin(), vectResult.end(), sensorId) != vectResult.end());
                REQUIRE_THROWS(query->getColumn("inexistantColumn"));
            }

            REQUIRE(resultNotEmpty);
        }
    }

    SECTION("extend with ratio=-2"){
        GeoFilter geoFilter1;

        BBox b = { 45, 30, 50, 4 };

        REQUIRE_NOTHROW(geoFilter1.setBBox(b));

        REQUIRE_THROWS(geoFilter1.extend(-2));
    }

}