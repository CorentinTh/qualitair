//
// Created by vwallyn on 18/02/19.
//

#include "catch2/catch.hpp"
#include <random>

#include "../../../src/Controller/include/CLIParser.h"


TEST_CASE("Testing CLIParser::getArgument", "[UT-C-1]") {
    std::vector<std::string> command1 = { "ingest", "--input=data" };
    CLIParser cliParser = CLIParser(command1);

    REQUIRE(cliParser.getArgument("input") == "data");
    REQUIRE(cliParser.getArgument("xxxx") == "");

    std::vector<std::string> command2 = { "ingest", "--input=" };
    cliParser = CLIParser(command2);

    REQUIRE(cliParser.getArgument("input") == "");

    std::vector<std::string> command3 = { "ingest", "--input=a", "--input=b" };
    cliParser = CLIParser(command3);

    REQUIRE(cliParser.getArgument("input") == "");

    std::vector<std::string> command4 = { "ingest", "--input=a", "--format=RAW" };
    cliParser = CLIParser(command4);

    REQUIRE(cliParser.getArgument("input") == "a");
    REQUIRE(cliParser.getArgument("format") == "RAW");
    REQUIRE(cliParser.getArgument("xxxxx") == "");
}