//
// Created by vwallyn on 18/02/19.
//

#include "catch2/catch.hpp"
#include <random>

#include "../../../src/Controller/include/Config.h"

TEST_CASE("Testing Config::load", "[UT-C-3]") {
    Config config = Config("tests/config-sample.ini");
    config.load();

    // TODO set actual values from sample file
    REQUIRE(config.getBrokenTime() == 0);
    REQUIRE(config.getEpsilon() == 5);
    REQUIRE(config.getThreshold() == 10);
    REQUIRE(config.getIGQAFormula() == "");
    REQUIRE(config.getSearchingGranularity() == 0);
    REQUIRE(config.getTimeThreshold() == 0);
    REQUIRE(config.getValueThreshold() == 0);
    REQUIRE(config.getAdmissibleRanges() == std::unordered_map<std::string, std::pair<int, int>>());



    // TODO test with broken file, missing conf ?
}