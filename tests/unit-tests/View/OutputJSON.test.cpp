//
// Created by vwallyn on 18/02/19.
//

#include "catch2/catch.hpp"
#include <string>
#include <iostream>
#include <fstream>
#include <istream>
#include <typeinfo>
#include <sstream>

#include "../../../src/View/include/OutputJSON.h"

std::string jsonFilename = "mon_dataset.json";
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


TEST_CASE("Test printSpikes(dataJSON) JSON", "[UT-V-11]") {

    OutputJSON myOutputGenerator = OutputJSON::getInstance();
    SECTION("is the method returning nothing"){
        REQUIRE(std::is_same<decltype(myOutputGenerator.printSpikes(dataJsonSpikes, jsonFilename)), void>::value);
    }
    SECTION("is the method creating the file"){
        myOutputGenerator.printSpikes(dataJsonSpikes, jsonFilename);
        std::ifstream file(jsonFilename);
        REQUIRE(file.good());
        file.close();
    }
    SECTION("is the method putting something in the json file"){
        myOutputGenerator.printSpikes(dataJsonSpikes, jsonFilename);
        std::ifstream out(jsonFilename);
        std::string line;
        int nbCharacters = 0;
        while(std::getline(out, line)){
            nbCharacters += line.length();
        }
        out.close();
        REQUIRE(nbCharacters>0);
    }
    SECTION("is the method putting the expected thing in the json file"){
        myOutputGenerator.printSpikes(dataJsonSpikes, jsonFilename);
        std::ifstream outToRead(jsonFilename);
        json j;
        outToRead >> j; // on convertit le json du fichier en un objet json
        REQUIRE(j==dataJsonSpikes);
    }
}

TEST_CASE("Test printStats(dataJSON) JSON", "[UT-V-12]") {

    OutputJSON myOutputGenerator = OutputJSON::getInstance();
    SECTION("is the method returning nothing"){
        REQUIRE(std::is_same<decltype(myOutputGenerator.printStats(dataJsonStats, jsonFilename)), void>::value);
    }
    SECTION("is the method creating the file"){
        myOutputGenerator.printStats(dataJsonStats, jsonFilename);
        std::ifstream file(jsonFilename);
        REQUIRE(file.good());
        file.close();
    }
    SECTION("is the method putting something in the json file"){
        myOutputGenerator.printStats(dataJsonStats, jsonFilename);
        std::ifstream out(jsonFilename);
        std::string line;
        int nbCharacters = 0;
        while(std::getline(out, line)){
            nbCharacters += line.length();
        }
        out.close();
        REQUIRE(nbCharacters>0);
    }
    SECTION("is the method putting the expected thing in the json file"){
        myOutputGenerator.printStats(dataJsonStats, jsonFilename);
        std::ifstream outToRead(jsonFilename);
        json j;
        outToRead >> j; // on convertit le json du fichier en un objet json
        REQUIRE(j==dataJsonStats);
    }
}

TEST_CASE("Test printSim(dataJSON) JSON", "[UT-V-13]") {

    OutputJSON myOutputGenerator = OutputJSON::getInstance();
    SECTION("is the method returning nothing"){
        REQUIRE(std::is_same<decltype(myOutputGenerator.printSim(dataJsonSim, jsonFilename)), void>::value);
    }
    SECTION("is the method creating the file"){
        myOutputGenerator.printSim(dataJsonSim, jsonFilename);
        std::ifstream file(jsonFilename);
        REQUIRE(file.good());
        file.close();
    }
    SECTION("is the method putting something in the json file"){
        myOutputGenerator.printSim(dataJsonSim, jsonFilename);
        std::ifstream out(jsonFilename);
        std::string line;
        int nbCharacters = 0;
        while(std::getline(out, line)){
            nbCharacters += line.length();
        }
        out.close();
        REQUIRE(nbCharacters>0);
    }
    SECTION("is the method putting the expected thing in the json file"){
        myOutputGenerator.printSim(dataJsonSim, jsonFilename);
        std::ifstream outToRead(jsonFilename);
        json j;
        outToRead >> j; // on convertit le json du fichier en un objet json
        REQUIRE(j==dataJsonSim);
    }
}

TEST_CASE("Test printBroken(dataJSON) JSON", "[UT-V-14]") {

    OutputJSON myOutputGenerator = OutputJSON::getInstance();
    SECTION("is the method returning nothing"){
        REQUIRE(std::is_same<decltype(myOutputGenerator.printBroken(dataJsonBroken, jsonFilename)), void>::value);
    }
    SECTION("is the method creating the file"){
        myOutputGenerator.printBroken(dataJsonBroken, jsonFilename);
        std::ifstream file(jsonFilename);
        REQUIRE(file.good());
        file.close();
    }
    SECTION("is the method putting something in the json file"){
        myOutputGenerator.printBroken(dataJsonBroken, jsonFilename);
        std::ifstream out(jsonFilename);
        std::string line;
        int nbCharacters = 0;
        while(std::getline(out, line)){
            nbCharacters += line.length();
        }
        out.close();
        REQUIRE(nbCharacters>0);
    }
    SECTION("is the method putting the expected thing in the json file"){
        myOutputGenerator.printBroken(dataJsonBroken, jsonFilename);
        std::ifstream outToRead(jsonFilename);
        json j;
        outToRead >> j; // on convertit le json du fichier en un objet json
        REQUIRE(j==dataJsonBroken);
    }
}

TEST_CASE("Test printIngest(dataJSON) JSON", "[UT-V-15]") {

    OutputJSON myOutputGenerator = OutputJSON::getInstance();
    SECTION("is the method returning nothing"){
        REQUIRE(std::is_same<decltype(myOutputGenerator.printIngest(dataJsonIngest, jsonFilename)), void>::value);
    }
    SECTION("is the method creating the file"){
        myOutputGenerator.printIngest(dataJsonIngest, jsonFilename);
        std::ifstream file(jsonFilename);
        REQUIRE(file.good());
        file.close();
    }
    SECTION("is the method putting something in the json file"){
        myOutputGenerator.printIngest(dataJsonIngest, jsonFilename);
        std::ifstream out(jsonFilename);
        std::string line;
        int nbCharacters = 0;
        while(std::getline(out, line)){
            nbCharacters += line.length();
        }
        out.close();
        REQUIRE(nbCharacters>0);
    }
    SECTION("is the method putting the expected thing in the json file"){
        myOutputGenerator.printIngest(dataJsonIngest, jsonFilename);
        std::ifstream outToRead(jsonFilename);
        json j;
        outToRead >> j; // on convertit le json du fichier en un objet json
        REQUIRE(j==dataJsonIngest);
    }
}