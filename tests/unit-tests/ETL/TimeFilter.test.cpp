#include "catch2/catch.hpp"
#include <string>
#include "../../../src/ETL/include/TimeFilter.h"
#include "../../../src/Data/include/ConnectionFactory.h"
#include "../../../src/Data/include/QueryBuilder.h"

using namespace std;


TEST_CASE("Testing TimeFilter with start", "[UT-E-3]") {
    SQLite::Database * database = ConnectionFactory::getConnection();
    ConnectionFactory::setDatabase("../tests/data/dbmock.sqlite");
    QueryBuilder queryBuilder = QueryBuilder();
    queryBuilder.select("rowid").from("Measurement");

    SQLite::Statement * query;

    TimeFilter timeFilter;

    time_t start = 1550150048;  // 14/02/2019 à 14:14:08

    CHECK_NOTHROW(timeFilter.setStart(start));
    timeFilter.applyTo(queryBuilder);

    CHECK_NOTHROW(query = queryBuilder.execute());

    vector<int> vectLineNumberResult;
    vectLineNumberResult.push_back(1);
    vectLineNumberResult.push_back(2);
    vectLineNumberResult.push_back(3);
    vectLineNumberResult.push_back(4);
    vectLineNumberResult.push_back(5);
    vectLineNumberResult.push_back(6);

    bool resultNotEmpty = false;

    while (query->executeStep()){
        resultNotEmpty = true;
        int rowId = query->getColumn("rowid");
        CHECK(std::find(vectLineNumberResult.begin(), vectLineNumberResult.end(), rowId) != vectLineNumberResult.end());
        CHECK_THROWS(query->getColumn("inexistantColumn"));
    }

    CHECK(resultNotEmpty);
}

TEST_CASE("Testing TimeFilter with end", "[UT-E-4]") {
    SQLite::Database * database = ConnectionFactory::getConnection();
    ConnectionFactory::setDatabase("../tests/data/dbmock.sqlite");
    QueryBuilder queryBuilder = QueryBuilder();
    queryBuilder.select("rowid").from("Measurement");

    SQLite::Statement * query;

    TimeFilter timeFilter;

    time_t end = 1550150048;  // 14/02/2019 à 14:14:08

    CHECK_NOTHROW(timeFilter.setEnd(end));
    timeFilter.applyTo(queryBuilder);

    CHECK_NOTHROW(query = queryBuilder.execute());

    CHECK(!query->executeStep());
}

TEST_CASE("Testing TimeFilter with start and end inverted", "[UT-E-3, UT-E-4]") {
    TimeFilter timeFilter;

    time_t end = 1550430257;    // 17/02/2019 à 19:04:17
    time_t start = 1550516657;  // 18/02/2019 à 19:04:17

    CHECK_NOTHROW(timeFilter.setStart(start));
    CHECK_THROWS(timeFilter.setEnd(end));
}

TEST_CASE("Testing TimeFilter with start and end equals", "[UT-E-3, UT-E-4]") {
    TimeFilter timeFilter;

    time_t t = 1550430257;  // 17/02/2019 à 19:04:17

    CHECK_NOTHROW(timeFilter.setStart(t));
    CHECK_THROWS(timeFilter.setEnd(t));
}

TEST_CASE("Testing TimeFilter with interval", "[UT-E-5]") {
    SQLite::Database * database = ConnectionFactory::getConnection();
    ConnectionFactory::setDatabase("../tests/data/dbmock.sqlite");
    QueryBuilder queryBuilder = QueryBuilder();
    queryBuilder.select("rowid").from("Measurement");

    SQLite::Statement * query;

    TimeFilter timeFilter;

    time_t start = 1550150154;    // 14/02/2019 à 14:15:54
    time_t end = 1550158002;  // 14/02/2019 à 16:26:42

    CHECK_NOTHROW(timeFilter.setInterval(start, end));
    timeFilter.applyTo(queryBuilder);

    CHECK_NOTHROW(query = queryBuilder.execute());

    vector<int> vectLineNumberResult;
    vectLineNumberResult.push_back(1);
    vectLineNumberResult.push_back(2);
    vectLineNumberResult.push_back(3);
    vectLineNumberResult.push_back(4);

    bool resultNotEmpty = false;

    while (query->executeStep()){
        resultNotEmpty = true;
        int rowId = query->getColumn("rowid");
        CHECK(std::find(vectLineNumberResult.begin(), vectLineNumberResult.end(), rowId) != vectLineNumberResult.end());
        CHECK_THROWS(query->getColumn("inexistantColumn"));
    }

    CHECK(resultNotEmpty);

}

TEST_CASE("Testing TimeFilter with interval inverted", "[UT-E-5]") {
    TimeFilter timeFilter;

    time_t end = 1550150154;    // 14/02/2019 à 14:15:54
    time_t start = 1550158002;  // 14/02/2019 à 16:26:42

    CHECK_THROWS(timeFilter.setInterval(start, end));
}

TEST_CASE("Testing TimeFilter with start and end equals on interval", "[UT-E-5]") {
    TimeFilter timeFilter;

    time_t t = 1550430257;  // 17/02/2019 à 19:04:17

    CHECK_THROWS(timeFilter.setInterval(t, t));
}
