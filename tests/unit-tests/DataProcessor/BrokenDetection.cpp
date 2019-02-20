//
// Created by vwallyn on 18/02/19.
//

#include "catch2/catch.hpp"


#include "../../../src/DataProcessor/include/BrokenDetection.h"

TEST_CASE("Testing broken detection", "[UT-DP-8]") {

    // FIXME when measurement class is merged, check order parameter
    std::vector<Measurement> measures = {
            Measurement(1, 1, 4, 1550150155),
            Measurement(2, 1, 5, 1550150156),
            Measurement(3, 2, 10, 1550151014),
            Measurement(3, 2, 28, 1550158000),
            Measurement(4, 3, 15, 1550150048),
            Measurement(5, 3, 11, 1550158049)
    };
    // FIXME when sensor class is merged, check order parameter
    std::vector<Sensor> sensors = {
            Sensor(1, 45.7574995, 4.8313017, "Bellecour - Grande roue"),
            Sensor(2, 45.7632485, 4.8335574, "Cordelier - Métro"),
            Sensor(3, 45.762994, 4.833632, "Rue de la république")
    };

    std::unordered_map<std::string, std::pair<int, int>> admissibleRanges = {
            {
                    "1",
                    std::pair<int,int>(1, 10)
            },
            {
                    "2",
                    std::pair<int,int>(5, 20)
            },
            {
                    "3",
                    std::pair<int,int>(1, 100)
            }
    };

    int timeThreshold = 10000;

    json ot5 = R"({
   {
      "id":71,
      "lat":48.597855,
      "long":3.401035,
    "description":"Pétaouchnok"
   },
   {
    "id":147,
    "lat":28.468412,
    "long":14.351684,
    "description":"Paris - Tour Eiffel"
   }
}
)"_json;


    BrokenDetection brokenDetection(measures, sensors, timeThreshold, admissibleRanges);
    CHECK(brokenDetection.apply() == ot5);

    timeThreshold = 10;
    // TODO refactor this test, useless if we change a parameter but the output doesn't ... what are we testing here ??
    BrokenDetection brokenDetection2(measures, sensors, timeThreshold, admissibleRanges);
    CHECK(brokenDetection2.apply() == ot5);
}