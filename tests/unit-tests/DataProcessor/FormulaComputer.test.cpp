////
//// Created by vwallyn on 18/02/19.
////
//
//#include "catch2/catch.hpp"
//
//
//#include "../../../src/DataProcessor/include/FormulaComputer.h"
//
//
//TEST_CASE("Testing formula computation", "[UT-DP-1]") {
//
//    FormulaComputer formulaComputer = FormulaComputer("{co2}/({co2}+{o2})");
//    pointCollection ds1 =   {
//            {
//                    {
//                            {
//                                    { "co2", 4 },
//                                    { "o2", 2 }
//                            }
//                    }
//            }
//    };
//
//    CHECK(formulaComputer.compute(ds1) == 0.67);
//
//    pointCollection ds2 = {
//            {
//                    {
//                            {
//                                    { "co2", 4 },
//                                    { "o2", 2 }
//                            },
//                            {
//                                    { "co2", 10 },
//                                    { "o2", 1 }
//                            }
//                    }
//
//            },
//    };
//
//    CHECK(formulaComputer.compute(ds2) == 0.82);
//
//    pointCollection ds3 =
//            {
//                    {
//                            {
//                                    {
//                                            { "co2", 5 },
//                                            { "o2",  3 }
//                                    },
//                                    {
//                                            { "co2", 7 },
//                                            { "o2", 4 }
//                                    }
//                            },
//                            {
//                                    {
//                                            { "co2", 7 },
//                                            { "o2", 5 }
//                                    },
//                                    {
//                                            { "co2", 3},
//                                            { "o2", 7 }
//                                    }
//                            }
//                    },
//                    {
//                            {
//                                    {
//                                            { "co2", 8 },
//                                            { "o2", 4 }
//                                    },
//                                    {
//                                            { "co2", 6},
//                                            { "o2", 1}
//                                    }
//                            },
//                            {
//                                    {
//                                            { "co2", 2 },
//                                            { "o2", 10 }
//                                    },
//                                    {
//                                            { "co2", 10},
//                                            { "o2", 5 }
//                                    }
//                            }
//                    }
//            };
//
//    CHECK(formulaComputer.compute(ds3) == 0.55);
//}