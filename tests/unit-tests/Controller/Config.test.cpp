//
// Created by vwallyn on 18/02/19.
//

#include "catch2/catch.hpp"
#include <random>

#include "../../../src/Controller/include/Config.h"
#include <unordered_map>
#include <string>
#include <utility>

TEST_CASE("Testing Config::load", "[UT-C-3]") {
    Config config = Config("data/config-sample.ini");
    config.load();

    // TODO set actual values from sample file
    REQUIRE(config.getBrokenTime() == 3600);
    REQUIRE(config.getEpsilon() == 5);
    REQUIRE(config.getThreshold() == 10);
    REQUIRE(config.getIGQAFormula() == "1/({attr1}+{attr2})+3*{attr3}");
    REQUIRE(config.getTemporalGranularity() == 1000);
    REQUIRE(config.getSpatialGranularity() == 1000);
    REQUIRE(config.getTimeThreshold() == 12);
    REQUIRE(config.getValueThreshold() == 500);
    REQUIRE(config.getMinimalArea() == 10000);

    REQUIRE(config.getAdmissibleRanges()
            ==
            (std::unordered_map<std::string, std::pair<int, int>>) {
                    {"attr1", {0,  15}},
                    {"attr2", {10, 100}},
            });



    // TODO test with broken file, missing conf ?
}