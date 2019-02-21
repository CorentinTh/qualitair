#include "catch2/catch.hpp"
#include "../../../src/ETL/include/ETL.h"
#include "../../utils.hpp"

#include "nlohmann/json.hpp"
using json = nlohmann::json;

using namespace std;


TEST_CASE("Testing ETL::ingest with clean csv string", "[UT-E-1]"){
    ETL etl = ETL::getInstance();


    json ret = etl.ingest({

    })

}