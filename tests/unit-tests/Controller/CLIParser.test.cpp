//
// Created by vwallyn on 18/02/19.
//

#include "easylogging++.h"  //
INITIALIZE_EASYLOGGINGPP    // Those line must be set only once in *.test.cpp files
#define CATCH_CONFIG_MAIN   //


#include "catch2/catch.hpp"
#include <random>
#include "../../../src/Controller/include/CLIParser.h"


TEST_CASE("Testing CLIParser::getArgument", "[UT-C-1]") {
    char* command1[] = { "ingest", "--input=data", NULL };
    CLIParser cliParser(command1);

    REQUIRE(cliParser.getArgument("input") == "data");
    REQUIRE(cliParser.getArgument("xxxx") == "");

    char* command2[] = { "ingest", "--input=", NULL  };
    cliParser = CLIParser(command2);

    REQUIRE(cliParser.getArgument("input") == "");

    char* command3[] = { "ingest", "--input=a", "--input=b" , NULL };
    cliParser = CLIParser(command3);

    REQUIRE(cliParser.getArgument("input") == "a");

    char* command4[] = { "ingest", "--input=a", "--format=RAW" , NULL };
    cliParser = CLIParser(command4);

    REQUIRE(cliParser.getArgument("input") == "a");
    REQUIRE(cliParser.getArgument("format") == "RAW");
    REQUIRE(cliParser.getArgument("xxxxx") == "");
}

TEST_CASE("Testing CLIParser::getVerb", "[UT-C-2]") {
    char* command1[] = { "ingest", "--input=data" , NULL };
    CLIParser cliParser = CLIParser(command1);

    REQUIRE(cliParser.getVerb() == "ingest");

    // TODO looks odd, remove the detect ?
    char* command2[] = { "sim" , NULL };
    cliParser = CLIParser(command2);

    REQUIRE(cliParser.getVerb() == "sim");

    char* command3[] = { "--input=.", "--bbox=a" , NULL };
    cliParser = CLIParser(command3);

    REQUIRE(cliParser.getVerb() == "");

}