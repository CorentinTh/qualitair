////
//// Created by vwallyn on 18/02/19.
////
//#include "catch2/catch.hpp"
//
//
//#include "../../../src/DataProcessor/include/Aggregation.h"
//
//namespace AggTest {
//
//
///* DATASETS */
//    std::string formula = "{co2}/({co2}+{o2})";
//    pointCollection ds1 = {
//            {
//                    {
//                            {
//                                    {"co2", 4},
//                                    {"o2", 2}
//                            }
//                    }
//            }
//    };
//
//    pointCollection ds2 = {
//            {
//                    {
//                            {
//                                    {"co2", 4},
//                                    {"o2", 2}
//                            },
//                            {
//                                    {"co2", 10},
//                                    {"o2", 1}
//                            }
//                    }
//
//            },
//    };
//
//    pointCollection ds3 =
//            {
//                    {
//                            {
//                                    {
//                                            {"co2", 5},
//                                            {"o2", 3}
//                                    },
//                                    {
//                                            {"co2", 7},
//                                            {"o2", 4}
//                                    }
//                            },
//                            {
//                                    {
//                                            {"co2", 7},
//                                            {"o2", 5}
//                                    },
//                                    {
//                                            {"co2", 3},
//                                            {"o2", 7}
//                                    }
//                            }
//                    },
//                    {
//                            {
//                                    {
//                                            {"co2", 8},
//                                            {"o2", 4}
//                                    },
//                                    {
//                                            {"co2", 6},
//                                            {"o2", 1}
//                                    }
//                            },
//                            {
//                                    {
//                                            {"co2", 2},
//                                            {"o2", 10}
//                                    },
//                                    {
//                                            {"co2", 10},
//                                            {"o2", 5}
//                                    }
//                            }
//                    }
//            };
///* END DATASETS */
//
//    TEST_CASE("Testing average", "[UT-DP-2]") {
//
//        std::unordered_map<std::string, double> out1 = {{"co2", 4},
//                                                        {"o2",  2}};
//        Aggregation agg(ds1);
//        CHECK(agg.computeAverage() == out1);
//
//        std::unordered_map<std::string, double> out2 = {
//                {"co2", 7},
//                {"o2",  1.5}
//        };
//        Aggregation agg2(ds2);
//        CHECK(agg2.computeAverage() == out2);
//
//
//        std::unordered_map<std::string, double> out3 = {
//                {"co2", 6},
//                {"o2",  4.88}
//        };
//        Aggregation agg3(ds3);
//        CHECK(agg3.computeAverage() == out3);
//    }
//
//    TEST_CASE("Testing extrems", "[UT-DP-3]") {
//
//        std::unordered_map<std::string, std::pair<double, double>> out1 = {
//                {"co2", {4, 4}},
//                {"o2",  {2, 2}}
//        };
//
//        Aggregation agg(ds1);
//        CHECK(agg.computeExtrems() == out1);
//
//        std::unordered_map<std::string, std::pair<double, double>> out2 = {
//                {"co2", {4, 10}},
//                {"o2",  {1, 2}}
//        };
//        Aggregation agg2(ds2);
//        CHECK(agg2.computeExtrems() == out2);
//
//
//        std::unordered_map<std::string, std::pair<double, double>> out3 = {
//                {"co2", {2, 10}},
//                {"o2",  {1, 10}}
//        };
//        Aggregation agg3(ds3);
//        CHECK(agg3.computeExtrems() == out3);
//    }
//
//    TEST_CASE("Testing deviation", "[UT-DP-4]") {
//        std::unordered_map<std::string, double> out1 = {
//                {"co2", 0},
//                {"o2",  0}
//        };
//        Aggregation agg(ds1);
//        CHECK(agg.computeDeviation() == out1);
//
//        std::unordered_map<std::string, double> out2 = {
//                {"co2", 3},
//                {"o2",  0.5}
//        };
//        Aggregation agg2(ds2);
//        CHECK(agg2.computeDeviation() == out2);
//
//
//        std::unordered_map<std::string, double> out3 = {
//                {"co2", 2.45},
//                {"o2",  2.52}
//        };
//        Aggregation agg3(ds3);
//        CHECK(agg3.computeDeviation() == out3);
//    }
//
//    TEST_CASE("Testing ATMO", "[UT-DP-5]") {
//
//        //TODO
//
//    }
//
//    TEST_CASE("Testing aggregation", "[UT-DP-6]") {
//
//        Aggregation agg(ds3);
//
//        json out = R"({
//            "co2" : {
//                "avg":6.0,
//                "min":2.0,
//                "max":10.0,
//                "deviation":2.45
//            },
//            "o2":{
//                "avg":4.88,
//                "min":1.0,
//                "max":10.0,
//                "deviation":2.52
//            },
//            "igqa": 0.55
//    })"_json;
//
//        CHECK(out.dump() == agg.apply()->dump());
//
//    }
//}