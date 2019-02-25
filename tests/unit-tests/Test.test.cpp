#define CATCH_CONFIG_MAIN   // This tells Catch to provide a main() - only do this in one cpp file

#include "catch2/catch.hpp"
#include <random>

#include "../../src/Test.h"


TEST_CASE("Testing add method", "[Test:add]") {

    for (int i = 0; i < 20; ++i) {
        int a = rand() % 100;
        int b = rand() % 100;

        Test test(a);

        REQUIRE(test.add(b) == (a + b));

    }
}