//
// Created by vwallyn on 18/02/19.
//

#include "catch2/catch.hpp"
#include <typeinfo>

#include "../../../src/DataProcessor/include/DataProcessor.h"

TEST_CASE("Testing singleton", "[UT-DP-9]") {
    REQUIRE(&DataProcessor::getInstance() == &DataProcessor::getInstance());
    
    REQUIRE(typeid(DataProcessor::getInstance()).name() == "DataProcessor");
}
