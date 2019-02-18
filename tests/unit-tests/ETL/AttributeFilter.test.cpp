#include "catch2/catch.hpp"
#include <string>
#include <vector>
#include "../../../src/ETL/include/AttributeFilter.h"
#include "../../utils.hpp"

using namespace std;

// TODO: add test id

TEST_CASE("Testing AttributeFilter::addAttribute", "[]") {
    AttributeFilter attributeFilter1;

    vector<string> attributes;

    for (int i = 0; i < 10; ++i) {
        string attribute = randomString(10);

        attributeFilter1.addAttribute(attribute);
        attributes.push_back(attribute);
    }

    CHECK(attributeFilter1.apply() == "sensorID in (" + join(attributes) + ")" );
}

TEST_CASE("Testing AttributeFilter::addAttributes", "[]") {
    AttributeFilter attributeFilter1;

    vector<string> attributes;

    for (int i = 0; i < 10; ++i) {
        string attribute = randomString(10);

        attributes.push_back(attribute);
    }
    attributeFilter1.addAttributes(attributes);

    CHECK(attributeFilter1.apply() == "sensorID in (" + join(attributes) + ")" );
}



TEST_CASE("Testing TimeFilter '=' operator", "[]") {
    AttributeFilter attributeFilter1, attributeFilter2;

    attributeFilter1.addAttribute(randomString(10));
    attributeFilter1 = attributeFilter2;

    SECTION("Equality") {
        CHECK(attributeFilter1.apply() == attributeFilter2.apply());
    }

    attributeFilter1.addAttribute(randomString(10));

    SECTION("Non-Equality") {
        CHECK(attributeFilter1.apply() != attributeFilter2.apply());
    }
}

