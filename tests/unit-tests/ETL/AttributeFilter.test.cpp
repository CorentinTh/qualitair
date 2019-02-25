#include "catch2/catch.hpp"
#include <string>
#include <vector>
#include "../../../src/ETL/include/AttributeFilter.h"
#include "../../utils.hpp"

using namespace std;

TEST_CASE("Testing AttributeFilter::addAttribute", "[UT-E-8]") {
    AttributeFilter attributeFilter1;

    attributeFilter1.addAttribute("attr1");
    attributeFilter1.addAttribute("attr2");
    attributeFilter1.addAttribute("attr3");

    CHECK(attributeFilter1.apply() == "sensorID in (attr1, attr2, attr3)" );
}

TEST_CASE("Testing AttributeFilter::addAttributes", "[UT-E-9]") {
    AttributeFilter attributeFilter1;

    vector<string> attributes;

    attributes.emplace_back("attr1");
    attributes.emplace_back("attr2");
    attributes.emplace_back("attr3");

    attributeFilter1.addAttributes(attributes);

    CHECK(attributeFilter1.apply() == "sensorID in (attr1, attr2, attr3)" );
}

TEST_CASE("Testing AttributeFilter '=' operator", "[extra]") {
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

