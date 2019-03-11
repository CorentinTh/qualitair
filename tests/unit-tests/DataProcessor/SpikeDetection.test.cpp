#include "catch2/catch.hpp"


#include "../../../src/DataProcessor/include/SpikeDetection.h"

namespace SpikeTest {


    TEST_CASE("Spike detection", "UT-DP-6") {
        SECTION("Test on simple point: > valueThreshold & > timeThreshold") {
            pointCollection in = {{{{{"co2", 10}}}}};
            json out = R"([[[[["co2",1]]]]])"_json;

            SpikeDetection spikeDetection(&in, 5, 0, 1, "co2");

            CHECK(spikeDetection.apply()->dump() == out.dump());
        }

        SECTION("Test on simple point: < valueThreshold & > timeThreshold") {
            pointCollection in = {{{{{"co2", 10}}}}};
            json out = R"([[[[["co2",0]]]]])"_json;

            SpikeDetection spikeDetection(&in, 20, 0, 1, "co2");

            CHECK(spikeDetection.apply()->dump() == out.dump());
        }

        SECTION("Test on simple point: > valueThreshold & < timeThreshold") {
            pointCollection in = {{{{{"co2", 10}}}}};
            json out = R"([[[[["co2",0]]]]])"_json;

            SpikeDetection spikeDetection(&in, 5, 0, 2, "co2");

            CHECK(spikeDetection.apply()->dump() == out.dump());
        }

        SECTION("Test on 3x3 grid: area threshold") {
            pointCollection in = {{
                                          {{{"co2", 10}}, {{"co2", 10}}, {{"co2", 10}}},
                                          {{{"co2", 10}}, {{"co2", 10}}, {{"co2", 10}}},
                                          {{{"co2", 10}}, {{"co2", 10}}, {{"co2", 10}}}
                                  }};


            json out = R"([[
[[["co2",0]],[["co2",0]],[["co2",0]]],
[[["co2",0]],[["co2",1]],[["co2",0]]],
[[["co2",0]],[["co2",0]],[["co2",0]]]
]])"_json;

            SpikeDetection spikeDetection(&in, 5, 1, 1, "co2");

            CHECK(spikeDetection.apply()->dump() == out.dump());
        }


        SECTION("Test on 3x5 grid: area threshold") {
            pointCollection in = {{
                                          {{{"co2", 10}}, {{"co2", 10}}, {{"co2", 10}}},
                                          {{{"co2", 10}}, {{"co2", 10}}, {{"co2", 10}}},
                                          {{{"co2", 10}}, {{"co2", 10}}, {{"co2", 10}}},
                                          {{{"co2", 10}}, {{"co2", 10}}, {{"co2", 10}}},
                                          {{{"co2", 10}}, {{"co2", 10}}, {{"co2", 10}}}
                                  }};


            json out = R"([[
[[["co2",0]],[["co2",0]],[["co2",0]]],
[[["co2",0]],[["co2",1]],[["co2",0]]],
[[["co2",0]],[["co2",1]],[["co2",0]]],
[[["co2",0]],[["co2",1]],[["co2",0]]],
[[["co2",0]],[["co2",0]],[["co2",0]]]
]])"_json;

            SpikeDetection spikeDetection(&in, 5, 1, 1, "co2");

            CHECK(spikeDetection.apply()->dump() == out.dump());
        }


        SECTION("Test on 5x5 grid: area threshold") {
            pointCollection in = {{
                                          {{{"co2", 10}}, {{"co2", 10}}, {{"co2", 10}}, {{"co2", 10}}, {{"co2", 10}}},
                                          {{{"co2", 10}}, {{"co2", 10}}, {{"co2", 10}}, {{"co2", 10}}, {{"co2", 10}}},
                                          {{{"co2", 10}}, {{"co2", 10}}, {{"co2", 10}}, {{"co2", 10}}, {{"co2", 10}}},
                                          {{{"co2", 10}}, {{"co2", 10}}, {{"co2", 10}}, {{"co2", 10}}, {{"co2", 10}}},
                                          {{{"co2", 10}}, {{"co2", 10}}, {{"co2", 10}}, {{"co2", 10}}, {{"co2", 10}}}
                                  }};


            json out = R"([[
[[["co2",0]],[["co2",0]],[["co2",0]],[["co2",0]],[["co2",0]]],
[[["co2",0]],[["co2",1]],[["co2",1]],[["co2",1]],[["co2",0]]],
[[["co2",0]],[["co2",1]],[["co2",1]],[["co2",1]],[["co2",0]]],
[[["co2",0]],[["co2",1]],[["co2",1]],[["co2",1]],[["co2",0]]],
[[["co2",0]],[["co2",0]],[["co2",0]],[["co2",0]],[["co2",0]]]
]])"_json;

            SpikeDetection spikeDetection(&in, 5, 1, 1, "co2");

            CHECK(spikeDetection.apply()->dump() == out.dump());
        }

        SECTION("Test on simple: time threshold") {
            pointCollection in = {{
                                          {{{"co2", 10}}},
                                  },{
                                          {{{"co2", 10}}},
                                  }};

            json out = R"([[[[["co2",0]]]],[[[["co2",1]]]]])"_json;

            SpikeDetection spikeDetection(&in, 5, 0, 2, "co2");

            CHECK(spikeDetection.apply()->dump() == out.dump());
        }

        SECTION("Test on simple: other attributes") {

            pointCollection in = {{
                                          {{{"co2", 10}, {"truc", 10}}},
                                  }};

            json out = R"([[[[["co2",1]]]]])"_json;

            SpikeDetection spikeDetection(&in, 5, 0, 1, "co2");

            CHECK(spikeDetection.apply()->dump() == out.dump());
        }
    }

}