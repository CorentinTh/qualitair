//
// Created by vwallyn on 18/02/19.
//

#include "catch2/catch.hpp"
#include <string>
#include <iostream>
#include <fstream>
#include <istream>
#include <typeinfo>

#include "../../../src/View/include/OutputHTML.h"

std::string htmlFilename = "mon_rapport_qualitair.html";
json dataJsonSpikes = {
        {"timestamp",  1550150155},
        {"latitude", 48.8534},
        {"longitude", 2.3488},
        {"pics", {
                               {
                                       {0, 1},
                                       {0, 0}
                               },
                               {
                                       {0, 1},
                                       {0, 0}
                               }
                       }
        }
};
json dataJsonStats = {
        {"co2", {
                        {"avg",6},
                        {"min",2},
                        {"max",10},
                        {"deviation",2.62}
                }
        },
        {"o2", {
                        {"avg", 4.88},
                        {"min", 1},
                        {"max", 10},
                        {"deviation", 2.70},
                }
        },
        {"igqa", 0.55}
};
json dataJsonSim = {
        {
                {
                        {"id",1},
                        {"lat",45.7574995},
                        {"long",4.8313017},
                        {"description","Bellecour - Grande roue"}
                },
                {
                        {"id",3},
                        {"lat",45.762994},
                        {"long",4.833632},
                        {"description","Rue de la république"}
                }
        }
};
json dataJsonBroken = {
        {
                {"id",71},
                {"lat",48.597855},
                        {"long",3.401035},
                {"description","Pétaouchnok"}
        },
        {
                {"id",147},
                {"lat"},28.468412,
                {"long",14.351684},
                {"description","Paris - Tour Eiffel"}
        }
};
json dataJsonIngest = {
        {"lines_inserted",4201},
        {"error",""}
};


TEST_CASE("Test printSpikes(dataJSON) HTML", "[UT-V-6]") {

    OutputHTML myOutputGenerator = OutputHTML::getInstance();
    SECTION("is the method returning nothing"){
        REQUIRE(std::is_same<decltype(myOutputGenerator.printSpikes(dataJsonSpikes, htmlFilename)), void>::value);
    }
    SECTION("is the method creating the file"){
        myOutputGenerator.printSpikes(dataJsonSpikes, htmlFilename);
        std::ifstream file(htmlFilename);
        REQUIRE(file.good());
        file.close();
    }
    SECTION("is the method putting something in the html file"){
        myOutputGenerator.printSpikes(dataJsonSpikes, htmlFilename);
        std::ifstream out(htmlFilename);
        std::string line;
        int nbCharacters = 0;
        while(std::getline(out, line)){
            nbCharacters += line.length();
        }
        out.close();
        REQUIRE(nbCharacters>0);
    }

}

TEST_CASE("Test printStats(dataJSON) HTML", "[UT-V-7]") {

    OutputHTML myOutputGenerator = OutputHTML::getInstance();
    SECTION("is the method returning nothing"){
        REQUIRE(std::is_same<decltype(myOutputGenerator.printStats(dataJsonStats, htmlFilename)), void>::value);
    }
    SECTION("is the method creating the file"){
        myOutputGenerator.printStats(dataJsonStats, htmlFilename);
        std::ifstream file(htmlFilename);
        REQUIRE(file.good());
        file.close();
    }
    SECTION("is the method putting something in the html file"){
        myOutputGenerator.printStats(dataJsonStats, htmlFilename);
        std::ifstream out(htmlFilename);
        std::string line;
        int nbCharacters = 0;
        while(std::getline(out, line)){
            nbCharacters += line.length();
        }
        out.close();
        REQUIRE(nbCharacters>0);
    }
}

TEST_CASE("Test printSim(dataJSON) HTML", "[UT-V-8]") {

    OutputHTML myOutputGenerator = OutputHTML::getInstance();
    SECTION("is the method returning nothing"){
        REQUIRE(std::is_same<decltype(myOutputGenerator.printSim(dataJsonSim, htmlFilename)), void>::value);
    }
    SECTION("is the method creating the file"){
        myOutputGenerator.printSim(dataJsonSim, htmlFilename);
        std::ifstream file(htmlFilename);
        REQUIRE(file.good());
        file.close();
    }
    SECTION("is the method putting something in the html file"){
        myOutputGenerator.printSim(dataJsonSim, htmlFilename);
        std::ifstream out(htmlFilename);
        std::string line;
        int nbCharacters = 0;
        while(std::getline(out, line)){
            nbCharacters += line.length();
        }
        out.close();
        REQUIRE(nbCharacters>0);
    }
}

TEST_CASE("Test printBroken(dataJSON) HTML", "[UT-V-9]") {

    OutputHTML myOutputGenerator = OutputHTML::getInstance();
    SECTION("is the method returning nothing"){
        REQUIRE(std::is_same<decltype(myOutputGenerator.printBroken(dataJsonBroken, htmlFilename)), void>::value);
    }
    SECTION("is the method creating the file"){
        myOutputGenerator.printBroken(dataJsonBroken, htmlFilename);
        std::ifstream file(htmlFilename);
        REQUIRE(file.good());
        file.close();
    }
    SECTION("is the method putting something in the html file"){
        myOutputGenerator.printBroken(dataJsonBroken, htmlFilename);
        std::ifstream out(htmlFilename);
        std::string line;
        int nbCharacters = 0;
        while(std::getline(out, line)){
            nbCharacters += line.length();
        }
        out.close();
        REQUIRE(nbCharacters>0);
    }
}

TEST_CASE("Test printIngest(dataJSON) HTML", "[UT-V-10]") {

    OutputHTML myOutputGenerator = OutputHTML::getInstance();
    SECTION("is the method returning nothing"){
        REQUIRE(std::is_same<decltype(myOutputGenerator.printIngest(dataJsonIngest, htmlFilename)), void>::value);
    }
    SECTION("is the method creating the file"){
        myOutputGenerator.printIngest(dataJsonIngest, htmlFilename);
        std::ifstream file(htmlFilename);
        REQUIRE(file.good());
        file.close();
    }
    SECTION("is the method putting something in the html file"){
        myOutputGenerator.printIngest(dataJsonIngest, htmlFilename);
        std::ifstream out(htmlFilename);
        std::string line;
        int nbCharacters = 0;
        while(std::getline(out, line)){
            nbCharacters += line.length();
        }
        out.close();
        REQUIRE(nbCharacters>0);
    }
}