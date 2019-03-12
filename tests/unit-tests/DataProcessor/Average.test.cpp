//
//        ----[  QUALIT'AIR  ]----
//
//    Marsaud Menseau Thomasset Wallyn
//  Copyright © 2019 - All right reserved
//

#include "catch2/catch.hpp"


#include "../../../src/DataProcessor/include/Average.h"

TEST_CASE("Testing average", "[UT-DP-2]") {
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

            }
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


    json out1 = R"({"avg":true,"co2":4.0,"o2":2.0})"_json;

    Average agg(ds1);
    CHECK(agg.apply()->dump() == out1.dump());

    json out2 = R"({"avg":true,"co2":7.0,"o2":1.5})"_json;
    Average agg2(ds2);
    CHECK(agg2.apply()->dump() == out2.dump());

    json out3 = R"({"avg":true,"co2":6.0,"o2":4.88})"_json;
    Average agg3(ds3);
    CHECK(agg3.apply()->dump() == out3.dump());
}