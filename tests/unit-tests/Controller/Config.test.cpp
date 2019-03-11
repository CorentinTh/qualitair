//
//        ----[  QUALIT'AIR  ]----
//
//    Marsaud Menseau Thomasset Wallyn
//  Copyright © 2019 - All right reserved
//

#include "catch2/catch.hpp"
#include <random>

#include "../../../src/Controller/include/Config.h"
#include <unordered_map>
#include <string>
#include <utility>

TEST_CASE("Testing Config::load", "[UT-C-4]") {
    Config config = Config("../tests/data/config-sample.ini");
    config.load();

    CHECK(config.getBrokenTime() == 3600);
    CHECK(config.getSimilarityThreshold() == 10);
    CHECK(config.getTemporalGranularity() == 7200);
    CHECK(config.getSpatialGranularity() == 0.05);
    CHECK(config.getSpikesTimeThreshold() == 12);
    CHECK(config.getSpikesValueThreshold() == 500.0);
    CHECK(config.getSpikesMinimalArea() == 10000.0);
    CHECK(config.getDatabaseFilepath() == "db.sqlite");

    CHECK(config.getAdmissibleRanges()
          ==
          (std::unordered_map<std::string, std::pair<double, double>>) {
                  {"O3",   {0, 400}},
                  {"PM10", {0, 120}},
                  {"SO2",  {0, 700}},
                  {"NO2",  {0, 600}}
          });


    Config config2 = Config("garbage");
    config2.load();

    CHECK(config2.getBrokenTime() == 0);
}