//
// Created by vwallyn on 18/02/19.
//

#include "catch2/catch.hpp"


#include "../../../src/DataProcessor/include/SimilarDetection.h"

TEST_CASE("Testing similar detection", "[UT-DP-7]") {

    json ot4 = R"(
{
  {
    {
        "id":1,
        "lat":45.7574995,
        "long":4.8313017,
        "description":"Bellecour - Grande roue"
    },
    {
        "id":3,
        "lat":45.762994,
        "long":4.833632,
        "description":"Rue de la république"
    }
  }
})"_json;

    /*
     * TODO
     * std::vector<Measurement> measures = {
            Measurement(1, 1, 4, 1550150155),
            Measurement(2, 1, 5, 1550150156),
            Measurement(3, 2, 10, 1550151014),
            Measurement(3, 2, 28, 1550158000),
            Measurement(4, 3, 15, 1550150048),
            Measurement(5, 3, 11, 1550158049)
    };

    std::vector<Sensor> sensors = {
            Sensor(1, 45.7574995, 4.8313017, "Bellecour - Grande roue"),
            Sensor(2, 45.7632485, 4.8335574, "Cordelier - Métro"),
            Sensor(3, 45.762994, 4.833632, "Rue de la république")
    };

    SimilarDetection similarDetection(measures, sensors, 50, 2);
    CHECK(similarDetection.apply()->dump() == ot4.dump());

    SimilarDetection similarDetection2(measures, sensors, 1, 3);
    CHECK(similarDetection2.apply()->dump() == (R"({})"_json).dump());*/

}