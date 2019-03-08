//
// Created by vwallyn on 18/02/19.
//

#include "catch2/catch.hpp"


#include "../../../src/DataProcessor/include/SimilarDetection.h"

TEST_CASE("Testing similar detection", "[UT-DP-7]") {

    std::vector<Measurement*> measures = {
           new Measurement(1550150156, Sensor("2", 45.7632485, 4.8335574, "Cordelier - Métro"), Attribute("1", "", ""), 5),
           new Measurement(1550151014, Sensor("3", 45.762994, 4.833632, "Rue de la république"), Attribute("2", "", ""), 10),
           new Measurement(1550158000, Sensor("3", 45.762994, 4.833632, "Rue de la république"), Attribute("2", "", ""), 28),
           new Measurement(1650158000, Sensor("3", 45.762994, 4.833632, "Rue de la république"), Attribute("2", "", ""), 28),
           new Measurement(1650158000, Sensor("3", 45.762994, 4.833632, "Rue de la république"), Attribute("1", "", ""), 28),
           new Measurement(1650158000, Sensor("3", 45.762994, 4.833632, "Rue de la république"), Attribute("1", "", ""), 28),
           new Measurement(1550151014, Sensor("147", 28.468412, 14.351684, "Paris - Tour Eiffel"), Attribute("3", "", ""), 1763),
           new Measurement(1550151014, Sensor("147", 28.468412, 14.351684, "Paris - Tour Eiffel"), Attribute("1", "", ""), 5),
           new Measurement(1550150032, Sensor("147", 28.468412, 14.351684, "Paris - Tour Eiffel"), Attribute("1", "", "") , 5),
           new Measurement(1550150032, Sensor("147", 28.468412, 14.351684, "Paris - Tour Eiffel"), Attribute("3", "", "") , 1765)
    };

    double threshold = 5;

    json ot4 = R"(
{
  "1": [
    [
      {
        "description": "Paris - Tour Eiffel",
        "id": "147",
        "lat": 28.468412,
        "long": 14.351684
      },
      {
        "description": "Cordelier - Métro",
        "id": "2",
        "lat": 45.7632485,
        "long": 4.8335574
      }
    ]
  ]
})"_json;

    double threshold2 = 90;

    json ot42 = R"(
{
  "1": [
    [
      {
        "description": "Rue de la république",
        "id": "3",
        "lat": 45.762994,
        "long": 4.833632
      },
      {
        "description": "Paris - Tour Eiffel",
        "id": "147",
        "lat": 28.468412,
        "long": 14.351684
      },
      {
        "description": "Cordelier - Métro",
        "id": "2",
        "lat": 45.7632485,
        "long": 4.8335574
      }
    ]
  ]
})"_json;



    SimilarDetection similarDetection(measures, threshold);
    CHECK(similarDetection.apply()->dump() == ot4.dump());

    SimilarDetection similarDetection2(measures, threshold2);
    CHECK(similarDetection2.apply()->dump() == ot42.dump());

}