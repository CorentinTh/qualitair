//
// Created by vwallyn on 18/02/19.
//

#include "catch2/catch.hpp"


#include "../../../src/DataProcessor/include/BrokenDetection.h"

TEST_CASE("Testing broken detection", "[UT-DP-8]") {

    std::vector<Measurement*> measures = {
            new Measurement(1550150156, Sensor("2", 45.7632485, 4.8335574, "Cordelier - Métro"), Attribute("1", "", ""), 5),
            new Measurement(1550151014, Sensor("3", 45.762994, 4.833632, "Rue de la république"), Attribute("2", "", ""), 10),
            new Measurement(1550158000, Sensor("3", 45.762994, 4.833632, "Rue de la république"), Attribute("2", "", ""), 28),
            new Measurement(1550151014, Sensor("147", 28.468412, 14.351684, "Paris - Tour Eiffel"), Attribute("3", "", ""), 1763),// superieur au range
            new Measurement(1550151014, Sensor("147", 28.468412, 14.351684, "Paris - Tour Eiffel"), Attribute("1", "", ""), 5),
            new Measurement(1550150032, Sensor("147", 28.468412, 14.351684, "Paris - Tour Eiffel"), Attribute("1", "", "") , 5),
            new Measurement(1550150032, Sensor("147", 28.468412, 14.351684, "Paris - Tour Eiffel"), Attribute("3", "", "") , 1765),
            new Measurement(1650158000, Sensor("3", 45.762994, 4.833632, "Rue de la république"), Attribute("2", "", ""), 28)
    };

    std::unordered_map<std::string, std::pair<double, double>> admissibleRanges = {
            {
                    "1",
                    std::pair<double,double>(1, 10)
            },
            {
                    "2",
                    std::pair<double,double>(5, 30)
            },
            {
                    "3",
                    std::pair<double,double>(1, 100)
            }
    };

    int timeThreshold = 1000;

    json ot5 = R"([
  {
    "start": 1550151014,
    "end": 1650158000,
    "sensor": {
      "id": "3",
      "lat": 45.762994,
      "long": 4.833632,
      "description": "Rue de la république"
    }
  },
  {
    "end": 1550150032,
    "sensor": {
      "description": "Paris - Tour Eiffel",
      "id": "147",
      "lat": 28.468412,
      "long": 14.351684
    },
    "start": 1550151014
  },
  {
    "end": 1650158000,
    "sensor": {
      "description": "Cordelier - Métro",
      "id": "2",
      "lat": 45.7632485,
      "long": 4.8335574
    },
    "start": 1550150156
  }
]
)"_json;


    BrokenDetection brokenDetection(measures, timeThreshold, admissibleRanges);
    CHECK(brokenDetection.apply()->dump() == ot5.dump());
}