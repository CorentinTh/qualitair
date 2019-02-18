//
// Created by vwallyn on 18/02/19.
//

#include <catch2/catch.hpp>
#include <SQLiteCpp/Database.h>
#include "../../../src/Data/include/ConnectionFactory.h"

TEST_CASE("Test ConnectionFactory::getConnection()", "[UT-D-1]") {
    SQLite::Database * database = ConnectionFactory::getConnection();

    REQUIRE(database != nullptr);
}