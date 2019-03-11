//
//        ----[  QUALIT'AIR  ]----
//
//    Marsaud Menseau Thomasset Wallyn
//  Copyright © 2019 - All right reserved
//

#include "catch2/catch.hpp"
#include "../../src/Controller/include/Cache.h"

TEST_CASE("Testing Cache", "UT-C-5") {
    Cache cache;

    auto j1 = R"(
  {
    "test": 10
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

    CHECK(cache.get(j2) == nullptr);

    Cache cache2;

    CHECK(*cache2.get(j1) == j2);

    remove("/tmp/.qualitair_cache");

    //TODO add test for partial match request
}