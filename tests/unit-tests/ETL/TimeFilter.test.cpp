#include "catch2/catch.hpp"
#include <string>
#include "../../../src/ETL/include/TimeFilter.h"

using namespace std;

TEST_CASE("Testing TimeFilter with start and end", "[UT-E-3, UT-E-4]") {
    TimeFilter timeFilter;

    time_t start = 1550430257;  // 17/02/2019 à 19:04:17
    time_t end = 1550516657;    // 18/02/2019 à 19:04:17

    timeFilter.setStart(start);
    timeFilter.setEnd(end);

    REQUIRE_THAT(timeFilter.apply(), "timestamp >= " + to_string(start) + " AND timestamp <= " + to_string(end));
}

TEST_CASE("Testing TimeFilter with start and end inverted", "[UT-E-3, UT-E-4]") {
    TimeFilter timeFilter;

    time_t end = 1550430257;    // 17/02/2019 à 19:04:17
    time_t start = 1550516657;  // 18/02/2019 à 19:04:17

    timeFilter.setStart(start);
    timeFilter.setEnd(end);

    REQUIRE_THROWS(timeFilter.apply());
}

TEST_CASE("Testing TimeFilter with start and end equals", "[UT-E-3, UT-E-4]") {
    TimeFilter timeFilter;

    time_t t = 1550430257;  // 17/02/2019 à 19:04:17

    timeFilter.setStart(t);
    timeFilter.setEnd(t);

    REQUIRE_THAT(timeFilter.apply(), "timestamp >= " + to_string(t) + " AND timestamp <= " + to_string(t));
}

TEST_CASE("Testing TimeFilter with interval", "[UT-E-5]") {
    TimeFilter timeFilter;

    time_t start = 1550430257;  // 17/02/2019 à 19:04:17
    time_t end = 1550516657;    // 18/02/2019 à 19:04:17

    timeFilter.setInterval(start, end);

    REQUIRE_THAT(timeFilter.apply(), "timestamp >= " + to_string(start) + " AND timestamp <= " + to_string(end));
}

TEST_CASE("Testing TimeFilter with interval inverted", "[UT-E-5]") {
    TimeFilter timeFilter;

    time_t end = 1550430257;    // 17/02/2019 à 19:04:17
    time_t start = 1550516657;  // 18/02/2019 à 19:04:17

    timeFilter.setInterval(start, end);

    REQUIRE_THROWS(timeFilter.apply());
}

TEST_CASE("Testing TimeFilter with start and end equals", "[UT-E-5]") {
    TimeFilter timeFilter;

    time_t t = 1550430257;  // 17/02/2019 à 19:04:17

    timeFilter.setInterval(t, t);

    REQUIRE_THAT(timeFilter.apply(), "timestamp = " + to_string(t));
}

TEST_CASE("Testing TimeFilter '=' operator", "[extra]") {
    TimeFilter timeFilter1, timeFilter2;

    time_t start = 1550430257;  // 17/02/2019 à 19:04:17
    time_t end = 1550516657;    // 18/02/2019 à 19:04:17

    timeFilter1.setStart(start);
    timeFilter1.setEnd(end);

    timeFilter2 = timeFilter1;

    SECTION("Equality") {
        CHECK(timeFilter1.apply() == timeFilter2.apply());
    }

    timeFilter1.setStart(start + 1000);

    SECTION("Non-Equality") {
        CHECK(timeFilter1.apply() != timeFilter2.apply());
    }
}
