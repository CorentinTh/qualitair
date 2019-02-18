#define CATCH_CONFIG_MAIN   // This tells Catch to provide a main() - only do this in one cpp file

#include "catch2/catch.hpp"
#include <string>
#include "../../../src/ETL/include/TimeFilter.h"

using namespace std;

// TODO: add test id

TEST_CASE("Testing TimeFilter with start and end", "[]") {
    TimeFilter timeFilter;

    time_t start = 1550430257;  // 17/02/2019 à 19:04:17
    time_t end = 1550516657;    // 18/02/2019 à 19:04:17

    timeFilter.setStart(start);
    timeFilter.setEnd(end);

    REQUIRE_THAT(timeFilter.apply(), "timestamp >= " + to_string(start) + " AND timestamp <= " + to_string(end));
}

TEST_CASE("Testing TimeFilter with start and end inverted", "[]") {
    TimeFilter timeFilter;

    time_t end = 1550430257;  // 17/02/2019 à 19:04:17
    time_t start = 1550516657;    // 18/02/2019 à 19:04:17

    timeFilter.setStart(start);
    timeFilter.setEnd(end);

    REQUIRE_THROWS(timeFilter.apply());
}

TEST_CASE("Testing TimeFilter with start and end equals", "[]") {
    TimeFilter timeFilter;

    time_t t = 1550430257;  // 17/02/2019 à 19:04:17

    timeFilter.setStart(t);
    timeFilter.setEnd(t);

    REQUIRE_THAT(timeFilter.apply(), "timestamp = " + to_string(t));
}

TEST_CASE("Testing TimeFilter with interval", "[]") {
    TimeFilter timeFilter;

    time_t start = 1550430257;  // 17/02/2019 à 19:04:17
    time_t end = 1550516657;    // 18/02/2019 à 19:04:17

    timeFilter.setInterval(start, end);

    REQUIRE_THAT(timeFilter.apply(), "timestamp >= " + to_string(start) + " AND timestamp <= " + to_string(end));
}

TEST_CASE("Testing TimeFilter with interval inverted", "[]") {
    TimeFilter timeFilter;

    time_t end = 1550430257;    // 17/02/2019 à 19:04:17
    time_t start = 1550516657;  // 18/02/2019 à 19:04:17

    timeFilter.setInterval(start, end);

    REQUIRE_THROWS(timeFilter.apply());
}

TEST_CASE("Testing TimeFilter with start and end equals", "[]") {
    TimeFilter timeFilter;

    time_t t = 1550430257;  // 17/02/2019 à 19:04:17

    timeFilter.setInterval(t, t);

    REQUIRE_THAT(timeFilter.apply(), "timestamp = " + to_string(t));
}


TEST_CASE("Testing TimeFilter '=' operator", "[]") {
    TimeFilter timeFilter1, timeFilter2, timeFilter3;

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
