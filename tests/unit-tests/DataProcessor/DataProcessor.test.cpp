//
// Created by vwallyn on 18/02/19.
//

#include "catch2/catch.hpp"
#include <typeinfo>

#include "../../../src/DataProcessor/include/DataProcessor.h"

TEST_CASE("Testing singleton", "[UT-DP-5]") {
    CHECK(&DataProcessor::getInstance() == &DataProcessor::getInstance());

    std::string type = typeid(DataProcessor::getInstance()).name();
    CHECK(type == "13DataProcessor");
}
