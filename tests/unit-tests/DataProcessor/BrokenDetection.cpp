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
}