#include "catch2/catch.hpp"
#include "../../../src/ETL/include/GeoFilter.h"
#include "../../utils.hpp"

using namespace std;

// TODO: add test id

TEST_CASE("Testing GeoFilter::setBBox with normal BBox", "[]") {
    GeoFilter geoFilter1;

    BBox b = { 45, 4, 50, 30 };

    geoFilter1.setBBox(b);

    CHECK(geoFilter1.apply() == "longitude >= 45 AND latitude >= 4 AND longitude <= 50 AND latitude <= 30");
}

TEST_CASE("Testing GeoFilter::setBBox with equal BBox", "[]") {
    GeoFilter geoFilter1;

    BBox b = {10, 10, 10, 10};

    geoFilter1.setBBox(b);

    CHECK(geoFilter1.apply() == "longitude >= 10 AND longitude <= 10 AND latitude >= 10 AND latitude <= 10");
}

TEST_CASE("Testing GeoFilter::setBBox with bad BBox", "[]") {
    GeoFilter geoFilter1;

    BBox b = {10, 11, -20, 21};

    geoFilter1.setBBox(b);

    REQUIRE_THROWS(geoFilter1.apply());
}

TEST_CASE("Testing GeoFilter::extend with ratio=2", "[]") {
    GeoFilter geoFilter1;

    BBox b = { 45, 4, 50, 30 };

    geoFilter1.setBBox(b);
    geoFilter1.extend(2);

    CHECK(geoFilter1.apply() == "longitude >= 22.5 AND latitude >= 2 AND longitude <= 100 AND latitude <= 60");
}

TEST_CASE("Testing GeoFilter::extend with ratio=0.5", "[]") {
    GeoFilter geoFilter1;

    BBox b = { 45, 4, 50, 30 };

    geoFilter1.setBBox(b);
    geoFilter1.extend(0.5);

    CHECK(geoFilter1.apply() == "longitude >= 67.5 AND latitude >= 6 AND longitude <= 25 AND latitude <= 15");
}

TEST_CASE("Testing GeoFilter::extend with ratio=-2", "[]") {
    GeoFilter geoFilter1;

    BBox b = { 45, 4, 50, 30 };

    geoFilter1.setBBox(b);
    geoFilter1.extend(-2);

    REQUIRE_THROWS(geoFilter1.apply());
}