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
    Config config = Config("../tests/data/config-sample.ini");
    config.load();

    REQUIRE(config.getBrokenTime() == 3600);
    REQUIRE(config.getSimilarityThreshold() == 10.0);
    REQUIRE(config.getTemporalGranularity() == 1000);
    REQUIRE(config.getSpatialGranularity() == 1000);
    REQUIRE(config.getSpikesTimeThreshold() == 12);
    REQUIRE(config.getSpikesValueThreshold() == 500.0);
    REQUIRE(config.getSpikesMinimalArea() == 10000.0);

    REQUIRE(config.getAdmissibleRanges()
            ==
            (std::unordered_map<std::string, std::pair<double, double>>) {
                    {"CO2", {0,  15}},
                    {"O2", {10, 100}},
            });



    // TODO test with broken file, missing conf ?
}