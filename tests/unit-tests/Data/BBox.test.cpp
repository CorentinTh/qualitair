//
// Created by vwallyn on 11/03/19.
//


#include <catch2/catch.hpp>
#include "../../../src/Data/include/BBox.h"

TEST_CASE("Test BBbox behavior", "[UT-D-1]") {

    SECTION("ctor") {
        BBox bbox(-8.085938, 37.317752, 27.333984, 22.836946);
        CHECK(bbox.getLeft() == -8.085938);
        CHECK(bbox.getBottom() == 22.836946);
        CHECK(bbox.getRight() == 27.333984);
        CHECK(bbox.getTop() == 37.317752);
    }

    SECTION("string ctor") {
        BBox bbox("-8.085938,22.836946,27.333984,37.317752");
        CHECK(bbox.getLeft() == -8.085938);
        CHECK(bbox.getBottom() == 22.836946);
        CHECK(bbox.getRight() == 27.333984);
        CHECK(bbox.getTop() == 37.317752);

        BBox bbox2("");
        CHECK(bbox2.isNull());
    }

    SECTION("isNull()") {
        BBox bbox("-8.085938,22.836946,27.333984,37.317752");
        CHECK(!bbox.isNull());

        BBox bbox2(-1,-1,-1,-1);
        CHECK(bbox2.isNull());

        BBox bbox3;
        CHECK(bbox3.isNull());
    }




}
