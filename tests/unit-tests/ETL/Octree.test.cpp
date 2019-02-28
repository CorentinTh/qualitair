//
// Created by cthomasset on 27/02/19.
//

#include "catch2/catch.hpp"
#include "../../../src/ETL/include/Octree.h"

using namespace OT;

struct isValue {
    int v;

    isValue(int v) : v(v) {}

    bool operator()(void *i) const { return (*(int *) i == v); }
};

bool valueInVector(const vector<void *> *vec, int val) {
    return find_if(vec->begin(), vec->end(), isValue(val)) != vec->end();
}

TEST_CASE("Quadtree border points in range") {
    Octree octree(new Boundary(0, 0, 0, 10, 10, 10));

    octree.insert({5, 5, 5, new int(0)});

    octree.insert({0, 0, 0, new int(1)});
    octree.insert({10, 0, 0, new int(2)});
    octree.insert({10, 10, 0, new int(3)});
    octree.insert({10, 10, 10, new int(4)});
    octree.insert({0, 10, 10, new int(5)});
    octree.insert({0, 0, 10, new int(6)});

    vector<void *> *res = octree.query(new Boundary(0, 0, 0, 10, 10, 10));

    SECTION("Result as proper size") {
        CHECK(res->size() == 7);
    }

    SECTION("Result contains all expected output") {
        for (int i = 0; i < 7; ++i) {
            SECTION(to_string(i) + " in result") {
                CHECK(valueInVector(res, i));
            }
        }

    }
}

TEST_CASE("Quadtree points out of range") {
    Octree octree(new Boundary(0, 0, 0, 10, 10, 10));

    octree.insert({11, 10, 0, new int(0)});
    octree.insert({-1, 10, -5, new int(1)});
    octree.insert({10, 11, 3, new int(2)});
    octree.insert({10, -1, 50, new int(3)});
    octree.insert({11, 11, 1, new int(4)});
    octree.insert({-1, -1, -1, new int(5)});

    vector<void *> *res = octree.query(new Boundary(0, 0, 0, 10, 10));

    CHECK(res->empty());
}

TEST_CASE("Quadtree points in same spot") {
    Octree octree(new Boundary(0, 0, 0, 10, 10, 10));

    octree.insert({1, 1, 1, new int(0)});
    octree.insert({1, 1, 1, new int(1)});
    octree.insert({3, 3, 3, new int(2)});
    octree.insert({3, 3, 3, new int(3)});
    octree.insert({3, 3, 3, new int(4)});

    vector<void *> *res = octree.query(new Boundary(0, 0, 0, 10, 10, 10));

    SECTION("Result as proper size") {
        CHECK(res->size() == 5);
    }

    SECTION("Result contains all expected output") {
        for (int i = 0; i < 5; ++i) {
            SECTION(to_string(i) + " in result") {
                CHECK(valueInVector(res, i));
            }
        }

    }
}


TEST_CASE("Quadtree points in sub-range") {
    Octree octree(new Boundary(0, 0, 0, 10, 10, 10));

    octree.insert({1, 1, 3, new int(0)});
    octree.insert({1, 2, 4, new int(1)});
    octree.insert({2, 3, 0, new int(2)});
    octree.insert({5, 5, 5, new int(3)});
    octree.insert({0, 0, 0, new int(4)});

    octree.insert({7, 7, 7, new int(5)});
    octree.insert({8, 7, 9, new int(6)});
    octree.insert({-1, 0, 100, new int(0)});

    vector<void *> *res = octree.query(new Boundary(0, 0, 0, 5, 5, 5));

    SECTION("Result as proper size") {
        CHECK(res->size() == 5);
    }

    SECTION("Result contains all expected output") {
        for (int i = 0; i < 5; ++i) {
            SECTION(to_string(i) + " in result") {
                CHECK(valueInVector(res, i));
            }
        }

    }

    SECTION("Result doesn't contain all expected output") {
        for (int i = 5; i < 8; ++i) {
            SECTION(to_string(i) + " in result") {
                CHECK(!valueInVector(res, i));
            }
        }

    }
}


TEST_CASE("Boundary contains match points") {
    Boundary b(5, 5, 5, 10, 10, 10);

    CHECK(b.contains({5, 5, 5}));
    CHECK(b.contains({10, 10, 10}));
    CHECK(b.contains({5, 6, 7}));
    CHECK(b.contains({7, 5, 9}));
    CHECK(b.contains({5, 9, 6}));

    CHECK(!b.contains({0, 0, 0}));
    CHECK(!b.contains({10, 0, 10}));
    CHECK(!b.contains({0, 10, 0}));
    CHECK(!b.contains({0, 20, -9}));
    CHECK(!b.contains({5, 20, 5}));
    CHECK(!b.contains({-5, 20, 42}));
    CHECK(!b.contains({-5, 20, 4}));
}


TEST_CASE("Boundary intersects") {
    Boundary b(5, 5, 5, 10, 10, 10);

    CHECK(b.intersects(new Boundary(7, 7, 7, 8, 8, 8)));
    CHECK(b.intersects(new Boundary(0, 0, 0, 20, 20, 20)));
    CHECK(b.intersects(new Boundary(7, 0, 0, 20, 7, 7)));
    CHECK(b.intersects(new Boundary(0, 0, 0, 7, 7, 7)));
    CHECK(b.intersects(new Boundary(7, 7, 7, 20, 20, 20)));
    CHECK(b.intersects(new Boundary(0, 7, 7, 20, 7, 20)));

    CHECK(!b.intersects(new Boundary(-10, -10, -10, -1 - 1, -1)));
    CHECK(!b.intersects(new Boundary(21, 21, 21, 22, 22, 22)));
    CHECK(!b.intersects(new Boundary(100, 100, 100, 100, 100, 100)));
}