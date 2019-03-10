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
    char* command1[] = { "./qualitair", "ingest", "--input=data", NULL };
    CLIParser cliParser(command1);

    CHECK(cliParser.getArgument("input") == "data");
    CHECK(cliParser.getArgument("xxxx") == "");

    char* command2[] = { "./qualitair", "ingest", "--input=", NULL  };
    cliParser = CLIParser(command2);

    CHECK(cliParser.getArgument("input") == "");

    char* command3[] = { "./qualitair", "ingest", "--input=a", "--input=b" , NULL };
    cliParser = CLIParser(command3);

    CHECK(cliParser.getArgument("input") == "a");

    char* command4[] = { "./qualitair","ingest", "--input=a", "--format=RAW" , NULL };
    cliParser = CLIParser(command4);

    CHECK(cliParser.getArgument("input") == "a");
    CHECK(cliParser.getArgument("format") == "RAW");
    CHECK(cliParser.getArgument("xxxxx") == "");

    char* command5[] = { "./qualitair","broken", "--start=2017-01-01 00:00:00", NULL };
    cliParser = CLIParser(command5);

    CHECK(cliParser.getArgument("start") == "2017-01-01 00:00:00");
}

TEST_CASE("Testing CLIParser::getVerb", "[UT-C-2]") {
    char* command1[] = { "./qualitair", "ingest", "--input=data" , NULL };
    CLIParser cliParser = CLIParser(command1);

    CHECK(cliParser.getVerb() == "ingest");

    char* command2[] = { "./qualitair", "similarities" , NULL };
    cliParser = CLIParser(command2);

    CHECK(cliParser.getVerb() == "similarities");

    char* command3[] = { "./qualitair", "--input=.", "--bbox=a" , NULL };
    cliParser = CLIParser(command3);

    CHECK(cliParser.getVerb() == "");

}

TEST_CASE("Testing CLIParser::getMandatoryArgument", "UT-C-3") {
    char* command1[] = { "./qualitair", "spikes", "CO2" , NULL };
    CLIParser cliParser = CLIParser(command1);

    CHECK(cliParser.getMandatoryArgument() == "CO2");

    char* command2[] = {  "./qualitair", "similarities" , NULL };
    cliParser = CLIParser(command2);

    CHECK_THROWS(cliParser.getMandatoryArgument());

    char* command3[] = { "./qualitair", "stats", "AVG", "--input=.", "--bbox=a" , NULL };
    cliParser = CLIParser(command3);

    CHECK_THROWS(cliParser.getMandatoryArgument(5));

}