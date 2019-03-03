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

    CHECK(config.getBrokenTime() == 3600);
    CHECK(config.getSimilarityThreshold() == 10.0);
    CHECK(config.getTemporalGranularity() == 1000);
    CHECK(config.getSpatialGranularity() == 1000);
    CHECK(config.getSpikesTimeThreshold() == 12);
    CHECK(config.getSpikesValueThreshold() == 500.0);
    CHECK(config.getSpikesMinimalArea() == 10000.0);

    CHECK(config.getAdmissibleRanges()
            ==
            (std::unordered_map<std::string, std::pair<double, double>>) {
                    {"CO2", {0,  15}},
                    {"O2", {10, 100}},
            });



    // TODO test with broken file, missing conf ?
}