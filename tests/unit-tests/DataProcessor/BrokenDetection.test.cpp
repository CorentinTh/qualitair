//
// Created by vwallyn on 18/02/19.
//

#include "catch2/catch.hpp"


#include "../../../src/DataProcessor/include/BrokenDetection.h"

TEST_CASE("Testing broken detection", "[UT-DP-8]") {

    std::vector<Measurement> measures = {
            Measurement(1550150156, Sensor("2", 45.7632485, 4.8335574, "Cordelier - Métro"), Attribute("1", "", ""), 5),
            Measurement(1550151014, Sensor("3", 45.762994, 4.833632, "Rue de la république"), Attribute("2", "", ""), 10),
            Measurement(1550158000, Sensor("3", 45.762994, 4.833632, "Rue de la république"), Attribute("2", "", ""), 28),
            Measurement(1550150048, Sensor("4", 45.7436395, 4.8801768, "Hôpital Edouard Herriot"), Attribute("3", "", ""), 15),
            Measurement(1548642848, Sensor("71", 48.597855, 3.401035, "Pétaouchnok"), Attribute("1", "", ""), 2.5), // 28/01/2019 à 03:34:08 derniere mesure
            Measurement(1550151014, Sensor("147", 28.468412, 14.351684, "Paris - Tour Eiffel"), Attribute("3", "", ""), 1763),// superieur au range
            Measurement(1550151014, Sensor("147", 28.468412, 14.351684, "Paris - Tour Eiffel"), Attribute("1", "", ""), 5),
            Measurement(1550150032, Sensor("147", 28.468412, 14.351684, "Paris - Tour Eiffel"), Attribute("1", "", "") , 5)

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
    "id":"71",
    "lat":48.597855,
    "long":3.401035,
    "description":"Pétaouchnok"
   },
   {
    "id":"147",
    "lat":28.468412,
    "long":14.351684,
    "description":"Paris - Tour Eiffel"
   }
}
)"_json;


    BrokenDetection brokenDetection(measures, timeThreshold, admissibleRanges);
    CHECK(brokenDetection.apply()->dump() == ot5.dump());

    timeThreshold = 10;

    // TODO refactor this test, useless if we change a parameter but the output doesn't ... what are we testing here ??
    BrokenDetection brokenDetection2(measures, timeThreshold, admissibleRanges);
    CHECK(brokenDetection2.apply()->dump() == ot5.dump());
}