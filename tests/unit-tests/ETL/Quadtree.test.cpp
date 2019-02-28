//
// Created by cthomasset on 27/02/19.
//

#include "catch2/catch.hpp"
#include "../../../src/ETL/include/Quadtree.h"

using namespace QT;

struct isValue {
    int v;

    isValue(int v) : v(v) {}

    bool operator()(void *i) const { return (*(int *) i == v); }
};

TEST_CASE("Quadtree border points in range") {
    Quadtree qt(new Boundary(0, 0, 10, 10));

    qt.insert({5, 5, new int(0)});    // middle center

    qt.insert({0, 5, new int(1)});    // middle left
    qt.insert({10, 5, new int(2)});   // middle right

    qt.insert({5, 0, new int(3)});    // top center
    qt.insert({5, 10, new int(4)});   // bottom center

    qt.insert({0, 0, new int(5)});    // top left
    qt.insert({10, 10, new int(6)});  // bottom right

    vector<void *> *res = qt.query(new Boundary(0, 0, 10, 10));

    SECTION("Result as proper size") {
        CHECK(res->size() == 7);
    }

    SECTION("Result contains all expected output") {
        for (int i = 0; i < 7; ++i) {
            SECTION(to_string(i) + " in result") {
                CHECK(find_if(res->begin(), res->end(), isValue(i)) != res->end());
            }
        }

    }
}

TEST_CASE("Quadtree points out of range") {
    Quadtree qt(new Boundary(0, 0, 10, 10));

    qt.insert({11, 10, new int(0)});
    qt.insert({-1, 10, new int(1)});
    qt.insert({10, 11, new int(2)});
    qt.insert({10, -1, new int(3)});
    qt.insert({11, 11, new int(4)});
    qt.insert({-1, -1, new int(5)});

    vector<void *> *res = qt.query(new Boundary(0, 0, 10, 10));

    CHECK(res->empty());
}


TEST_CASE("Quadtree points in same spot") {
    Quadtree qt(new Boundary(0, 0, 10, 10));

    qt.insert({1, 1, new int(0)});
    qt.insert({1, 1, new int(1)});
    qt.insert({2, 2, new int(2)});
    qt.insert({2, 2, new int(3)});
    qt.insert({2, 2, new int(4)});
//    qt.insert({2, 2, new int(5)});
//    qt.insert({2, 2, new int(6)});

    vector<void *> *res = qt.query(new Boundary(0, 0, 10, 10));

    SECTION("Result as proper size") {
        CHECK(res->size() == 7);
    }

    SECTION("Result contains all expected output") {
        for (int i = 0; i < 7; ++i) {
            SECTION(to_string(i) + " in result") {
                CHECK(find_if(res->begin(), res->end(), isValue(i)) != res->end());
            }
        }

    }
}


TEST_CASE("Quadtree points in sub-range") {
    Quadtree qt(new Boundary(0, 0, 10, 10));

    qt.insert({1, 1, new int(0)});
    qt.insert({1, 2, new int(1)});

    vector<void *> *res = qt.query(new Boundary(0, 0, 10, 10));

    CHECK(res->empty());


}