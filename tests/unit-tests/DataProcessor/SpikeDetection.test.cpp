//
// Created by vwallyn on 18/02/19.
//

#include "catch2/catch.hpp"


#include "../../../src/DataProcessor/include/SpikeDetection.h"

namespace SpikeTest {


/* DATASETS */
    std::string formula = "{co2}/({co2}+{o2})";
    pointCollection ds3 =
            {
                    {
                            {
                                    {
                                            {"co2", 5},
                                            {"o2", 3}
                                    },
                                    {
                                            {"co2", 7},
                                            {"o2", 4}
                                    }
                            },
                            {
                                    {
                                            {"co2", 7},
                                            {"o2", 5}
                                    },
                                    {
                                            {"co2", 3},
                                            {"o2", 7}
                                    }
                            }
                    },
                    {
                            {
                                    {
                                            {"co2", 8},
                                            {"o2", 4}
                                    },
                                    {
                                            {"co2", 6},
                                            {"o2", 1}
                                    }
                            },
                            {
                                    {
                                            {"co2", 2},
                                            {"o2", 10}
                                    },
                                    {
                                            {"co2", 10},
                                            {"o2", 5}
                                    }
                            }
                    }
            };
/* END DATASETS */

    TEST_CASE("Testing spike detection", "[UT-DP-6]") {

        // one spike
        json out1 = R"([[[[0,1],[0,0]],[[0,1],[0,0]]]])"_json;
        SpikeDetection spikeDetection(ds3, formula, 0.63, 1, 2);
        CHECK(spikeDetection.apply() == out1);

        // multiple spikes
        json out2 = R"([[[1,1],[0,0]],[[1,1],[0,0]]])"_json;
        SpikeDetection spikeDetection2(ds3, formula, 0.5, 1, 2);
        CHECK(spikeDetection2.apply() == out2);

        // no spike
        json out3 = R"([[[0,0],[0,0]],[[0,0],[0,0]]])"_json;
        SpikeDetection spikeDetection3(ds3, formula, 0.8, 1, 2);
        CHECK(spikeDetection3.apply() == out3);
    }

}