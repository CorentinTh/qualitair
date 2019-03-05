#include <iostream>
#include "easylogging++.h"
#include "DataProcessor/include/SpikeDetection.h"

using namespace std;

INITIALIZE_EASYLOGGINGPP

/**
 * "Please note that INITIALIZE_EASYLOGGINGPP should be used once and once-only otherwise you will end up getting
 * compilation errors. This is definiting several extern variables. This means it can be defined only once per
 * application. Best place to put this initialization statement is in file where int main(int, char**) function is
 * defined, right after last include statement."
 *
 * On le mettra qqlque part dans le controler pour avoir un main vide et propre.
 */




/**
 * Main function
 * @param {int} argc - Argument count
 * @param {char**} argv - Argument string array
 * @return {int}
 */
int main(int argc, char ** argv){
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

    pointCollection in = {{
        {{{"co2", 10}},{{"co2", 10}},{{"co2", 10}}},
        {{{"co2", 10}},{{"co2", 10}},{{"co2", 10}}},
        {{{"co2", 10}},{{"co2", 10}},{{"co2", 10}}}}
    };

    SpikeDetection spikeDetection(&in, 5, 1, 1, "co2");


    auto res = spikeDetection.apply();
    cout << res->dump();
    return 0;
}

