//
// Created by vwallyn on 02/03/19.
//

#include "catch2/catch.hpp"
#include "../../src/Controller/include/Cache.h"

TEST_CASE("Testing Cache", "") {
    Cache cache;

    auto j1 = R"(
  {
    "test": "x"
  }
)"_json;

    auto j2 = R"(
  {
    "happy": true,
    "pi": 3.141
  }
)"_json;
    cache.put(j1, j2);

    CHECK(*cache.get(j1) == j2);

    Cache cache2;

    CHECK(*cache2.get(j1) == j2);

    remove("/tmp/.qualitair_cache");
}