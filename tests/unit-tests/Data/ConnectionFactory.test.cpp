//
//        ----[  QUALIT'AIR  ]----
//
//    Marsaud Menseau Thomasset Wallyn
//  Copyright © 2019 - All right reserved
//

#include <catch2/catch.hpp>
#include <SQLiteCpp/Database.h>
#include "../../../src/Data/include/ConnectionFactory.h"

TEST_CASE("Test ConnectionFactory::getConnection()", "[UT-D-1]") {
    SQLite::Database *database = ConnectionFactory::getConnection();

    REQUIRE(database != nullptr);
    REQUIRE(database == ConnectionFactory::getConnection());
}
