//
//        ----[  QUALIT'AIR  ]----
//
//    Marsaud Menseau Thomasset Wallyn
//  Copyright © 2019 - All right reserved
//

#include "catch2/catch.hpp"
#include <string>
#include "../../../src/ETL/include/TimeFilter.h"
#include "../../../src/Data/include/ConnectionFactory.h"
#include "../../../src/Data/include/QueryBuilder.h"

using namespace std;


TEST_CASE("Testing TimeFilter::setStart et setEnd", "[UT-E-4]") {

    SECTION("with start") {
        SQLite::Database *database = ConnectionFactory::getConnection();
        ConnectionFactory::setDatabase("../tests/data/dbmock.sqlite");
        QueryBuilder queryBuilder = QueryBuilder();
        queryBuilder.select("rowid").from("Measurement");

        SQLite::Statement *query;

        TimeFilter timeFilter;

        time_t start = 1550150048;  // 14/02/2019 à 14:14:08

        REQUIRE_NOTHROW(timeFilter.setStart(start));
        timeFilter.applyTo(queryBuilder);

        REQUIRE_NOTHROW(query = queryBuilder.execute());

        vector<int> vectLineNumberResult;
        vectLineNumberResult.push_back(1);
        vectLineNumberResult.push_back(2);
        vectLineNumberResult.push_back(3);
        vectLineNumberResult.push_back(4);
        vectLineNumberResult.push_back(5);
        vectLineNumberResult.push_back(6);

        bool resultNotEmpty = false;

        while (query->executeStep()) {
            resultNotEmpty = true;
            int rowId = query->getColumn("rowid");
            REQUIRE(std::find(vectLineNumberResult.begin(), vectLineNumberResult.end(), rowId) != vectLineNumberResult.end());
            REQUIRE_THROWS(query->getColumn("inexistantColumn"));
        }

        REQUIRE(resultNotEmpty);
    }

    SECTION("with end") {
        SQLite::Database *database = ConnectionFactory::getConnection();
        ConnectionFactory::setDatabase("../tests/data/dbmock.sqlite");
        QueryBuilder queryBuilder = QueryBuilder();
        queryBuilder.select("rowid").from("Measurement");

        SQLite::Statement *query;

        TimeFilter timeFilter;

        time_t end = 1550150048;  // 14/02/2019 à 14:14:08

        REQUIRE_NOTHROW(timeFilter.setEnd(end));
        timeFilter.applyTo(queryBuilder);

        REQUIRE_NOTHROW(query = queryBuilder.execute());

        REQUIRE(!query->executeStep());
    }

    SECTION ("with start and end inverted") {
        TimeFilter timeFilter;

        time_t end = 1550430257;    // 17/02/2019 à 19:04:17
        time_t start = 1550516657;  // 18/02/2019 à 19:04:17

        REQUIRE_NOTHROW(timeFilter.setStart(start));
        REQUIRE_THROWS(timeFilter.setEnd(end));
    }

    SECTION ("with start and end equals") {
        TimeFilter timeFilter;

        time_t t = 1550430257;  // 17/02/2019 à 19:04:17

        REQUIRE_NOTHROW(timeFilter.setStart(t));
        REQUIRE_THROWS(timeFilter.setEnd(t));
    }
}


TEST_CASE("Testing TimeFilter::setInterval", "[UT-E-5]") {

    SECTION("with interval") {
        SQLite::Database *database = ConnectionFactory::getConnection();
        ConnectionFactory::setDatabase("../tests/data/dbmock.sqlite");
        QueryBuilder queryBuilder = QueryBuilder();
        queryBuilder.select("rowid").from("Measurement");

        SQLite::Statement *query;

        TimeFilter timeFilter;

        time_t start = 1550150154;    // 14/02/2019 à 14:15:54
        time_t end = 1550158002;  // 14/02/2019 à 16:26:42

        REQUIRE_NOTHROW(timeFilter.setInterval(start, end));
        timeFilter.applyTo(queryBuilder);

        REQUIRE_NOTHROW(query = queryBuilder.execute());

        vector<int> vectLineNumberResult;
        vectLineNumberResult.push_back(1);
        vectLineNumberResult.push_back(2);
        vectLineNumberResult.push_back(3);
        vectLineNumberResult.push_back(4);

        bool resultNotEmpty = false;

        while (query->executeStep()) {
            resultNotEmpty = true;
            int rowId = query->getColumn("rowid");
            REQUIRE(std::find(vectLineNumberResult.begin(), vectLineNumberResult.end(), rowId) != vectLineNumberResult.end());
            REQUIRE_THROWS(query->getColumn("inexistantColumn"));
        }

        REQUIRE(resultNotEmpty);
    }

    SECTION("with interval inverted") {
        TimeFilter timeFilter;

        time_t end = 1550150154;    // 14/02/2019 à 14:15:54
        time_t start = 1550158002;  // 14/02/2019 à 16:26:42

        REQUIRE_THROWS(timeFilter.setInterval(start, end));
    }

    SECTION("with start and end equals") {
        TimeFilter timeFilter;

        time_t t = 1550430257;  // 17/02/2019 à 19:04:17

        REQUIRE_THROWS(timeFilter.setInterval(t, t));
    }
}
