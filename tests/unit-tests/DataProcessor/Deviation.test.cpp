//
// Created by vwallyn on 03/03/19.
//

#include "catch2/catch.hpp"


#include "../../../src/DataProcessor/include/Deviation.h"

TEST_CASE("Testing deviation", "[UT-DP-4]") {

    /* DATASETS */
    pointCollection ds1 = {
            {
                    {
                            {
                                    {"co2", 4},
                                    {"o2", 2}
                            }
                    }
            }
    };

    pointCollection ds2 = {
            {
                    {
                            {
                                    {"co2", 4},
                                    {"o2", 2}
                            },
                            {
                                    {"co2", 10},
                                    {"o2", 1}
                            }
                    }

            },
    };

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
    json out1 = R"({"co2":0.0,"o2":0.0})"_json;
    Deviation agg(ds1);
    CHECK(agg.apply()->dump() == out1.dump());

    json out2 = R"({"co2":3.0,"o2":0.5})"_json;
    Deviation agg2(ds2);
    CHECK(agg2.apply()->dump() == out2.dump());

    json out3 = R"({"co2":2.45,"o2":2.52})"_json;
    Deviation agg3(ds3);
    CHECK(agg3.apply()->dump() == out3.dump());
}
