//
// Created by vwallyn on 18/02/19.
//

#include "catch2/catch.hpp"


#include "../../../src/DataProcessor/include/FormulaComputer.h"


TEST_CASE("Testing formula computation", "[UT-DP-1]") {

    FormulaComputer formulaComputer = FormulaComputer("{co2}/({co2}+{o2})");
    //formulaComputer.compute();
}