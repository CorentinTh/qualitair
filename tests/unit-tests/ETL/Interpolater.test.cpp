#include "catch2/catch.hpp"

#include "../../../src/ETL/include/Interpolater.h"


// TODO: add input and output

TEST_CASE("", "[]") {
    Interpolater interpolater;

    vector<Measurement> input = {};

    pointCollection output = {{{{{"type", 1}}}}};

//    REQUIRE(interpolater.interpolate(input, 10, 10) == output);

}