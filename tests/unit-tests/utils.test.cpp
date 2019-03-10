//
// Created by Bastien Marsaud on 10/03/2019.
//

#include "catch2/catch.hpp"
#include "../../src/utils.h"

TEST_CASE("Test parseRFC3339Date to timestamp", "[UT-Utils-1]") {
    std::string date = "2019-03-10 10:36:15";
    long expectedTimestamp = 1552210575000;

    CHECK(utils::parseRFC3339Date(date) == expectedTimestamp);
    CHECK(utils::parseRFC3339Date("") == 0);
}

TEST_CASE("Test parseISO8601Date to timestamp", "[UT-Utils-2]") {
    std::string date = "2017-01-01T16:31:14.2420000";
    long expectedTimestamp = 1483284674242;

    CHECK(utils::parseISO8601Date(date) == expectedTimestamp);
    CHECK(utils::parseISO8601Date("") == 0);
}

TEST_CASE("Test unjoinString", "[UT-Utils-3]") {
    std::string input1 = "a,b,c";
    std::string input2 = "a,  b, c";
    std::string input3 = "a";
    std::string input4 = "";
    
    std::vector<std::string> output1 = {"a", "b", "c"};
    std::vector<std::string> output2 = {"a", "  b", " c"};
    std::vector<std::string> output3 = {"a"};
    std::vector<std::string> output4;
    
    CHECK(utils::unjoinString(input1) == output1);
    CHECK(utils::unjoinString(input2) == output2);
    CHECK(utils::unjoinString(input3) == output3);
    CHECK(utils::unjoinString(input4) == output4);
    
}