//
// Created by Bastien Marsaud on 10/03/2019.
//

#include "catch2/catch.hpp"
#include "../../src/utils.h"

TEST_CASE("Test parseRFC3339Date to timestamp", "[UT-Utils-1]") {
    std::string date = "2019-03-10 10:36:15";
    long expectedTimestamp = 1552210575000;

    CHECK(parseRFC3339Date(date) == expectedTimestamp);
}

TEST_CASE("Test parseISO8601Date to timestamp", "[UT-Utils-2]") {
    std::string date = "2017-01-01T16:31:14.2420000";
    long expectedTimestamp = 1483284674242;

    CHECK(parseISO8601Date(date) == expectedTimestamp);
}