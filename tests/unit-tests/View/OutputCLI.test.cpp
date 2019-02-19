//
// Created by vwallyn on 18/02/19.
//

#include "catch2/catch.hpp"
#include <string>
#include <iostream>
#include <fstream>
#include <istream>
#include <typeinfo>

#include "../../../src/View/include/OutputCLI.h"

std::string dataJsonSpikes = "{ \
    \"timestamp\" :  1550150155, \
    \"latitude\" : 48.8534, \
    \"longitude\" : 2.3488, \
    \"pics\" : { \
            { \
                { \
                    0, \
                    1 \
                },\
                {\
                    0, \
                    0 \
                } \
            }, \
            { \
                { \
                    0, \
                    1 \
                }, \
                { \
                    0, \
                    0 \
                } \
            } \
    } \
};";
std::string dataJsonStats = "{ \
  \"co2\" : { \
      \"avg\":6, \
      \"min\":2, \
      \"max\":10, \
      \"deviation\":2.62 \
  }, \
  \"o2\":{ \
      \"avg\":4.88, \
      \"min\":1, \
      \"max\":10, \
      \"deviation\":2.70, \
  }, \
  \"igqa\": 0.55 \
};";
std::string dataJsonSim = "{ \
  { \
    { \
      \"id\":1, \
      \"lat\":45.7574995, \
      \"long\":4.8313017, \
      \"description\":\"Bellecour - Grande roue\" \
    }, \
    { \
      \"id\":3, \
      \"lat\":45.762994, \
      \"long\":4.833632, \
      \"description\":\"Rue de la république\" \
    } \
  } \
}";
std::string dataJsonBroken = "{ \
  {  \
    \"id\":71, \
    \"lat\":48.597855, \
    \"long\":3.401035, \
    \"description\":\"Pétaouchnok\" \
  }, \
  {  \
    \"id\":147,  \
    \"lat\":28.468412, \
    \"long\":14.351684, \
    \"description\":\"Paris - Tour Eiffel\" \
  } \
}";
std::string dataJsonIngest = "{ \
    \"lines_inserted\":4201 \
    \"error\":"" \
}";


TEST_CASE("Test printSpikes(dataJSON) CLI", "[UT-V-1]") {

    OutputCLI myOutputGenerator = OutputCLI::getInstance();
    REQUIRE(typeid(myOutputGenerator.getInstance()).name()=="OutputCLI");
    SECTION("is the method returning something"){
        REQUIRE(std::is_same<decltype(myOutputGenerator.printSpikes(dataJsonSpikes)), void>::value);
    }
    SECTION("is the method putting something in cout"){
        std::ofstream out("out.txt"); // mettre dans dossier bin ?
        std::streambuf *coutbuf = std::cout.rdbuf(); //save old buf
        std::cout.rdbuf(out.rdbuf()); //redirect std::cout to out.txt!
        myOutputGenerator.printSpikes(dataJsonSpikes);
        out.close();

        std::ifstream outToRead("out.txt");
        std::string line;
        int nbCharacters = 0;
        while(std::getline(outToRead, line)){
            nbCharacters += line.length();
        }
        outToRead.close();
        REQUIRE(nbCharacters>0);
    }

}

TEST_CASE("Test printStats(dataJSON) CLI", "[UT-V-2]") {

    OutputCLI myOutputGenerator = OutputCLI::getInstance();
    REQUIRE(typeid(myOutputGenerator.getInstance()).name()=="OutputCLI");
    SECTION("is the method returning something"){
        REQUIRE(std::is_same<decltype(myOutputGenerator.printStats(dataJsonStats)), void>::value);
    }
    SECTION("is the method putting something in cout"){
        std::ofstream out("out.txt"); // mettre dans dossier bin ?
        std::streambuf *coutbuf = std::cout.rdbuf(); //save old buf
        std::cout.rdbuf(out.rdbuf()); //redirect std::cout to out.txt!
        myOutputGenerator.printStats(dataJsonStats);
        out.close();

        std::ifstream outToRead("out.txt");
        std::string line;
        int nbCharacters = 0;
        while(std::getline(outToRead, line)){
            nbCharacters += line.length();
        }
        outToRead.close();
        REQUIRE(nbCharacters>0);
    }

}

TEST_CASE("Test printSim(dataJSON) CLI", "[UT-V-3]") {

    OutputCLI myOutputGenerator = OutputCLI::getInstance();
    REQUIRE(typeid(myOutputGenerator.getInstance()).name()=="OutputCLI");
    SECTION("is the method returning something"){
        REQUIRE(std::is_same<decltype(myOutputGenerator.printSim(dataJsonSim)), void>::value);
    }
    SECTION("is the method putting something in cout"){
        std::ofstream out("out.txt"); // mettre dans dossier bin ?
        std::streambuf *coutbuf = std::cout.rdbuf(); //save old buf
        std::cout.rdbuf(out.rdbuf()); //redirect std::cout to out.txt!
        myOutputGenerator.printSim(dataJsonSim);
        out.close();

        std::ifstream outToRead("out.txt");
        std::string line;
        int nbCharacters = 0;
        while(std::getline(outToRead, line)){
              nbCharacters += line.length();
        }
        outToRead.close();
        REQUIRE(nbCharacters>0);
    }

}

TEST_CASE("Test printBroken(dataJSON) CLI", "[UT-V-4]") {

    OutputCLI myOutputGenerator = OutputCLI::getInstance();
    REQUIRE(typeid(myOutputGenerator.getInstance()).name()=="OutputCLI");
    SECTION("is the method returning something"){
        REQUIRE(std::is_same<decltype(myOutputGenerator.printBroken(dataJsonBroken)), void>::value);
    }
    SECTION("is the method putting something in cout"){
        std::ofstream out("out.txt"); // mettre dans dossier bin ?
        std::streambuf *coutbuf = std::cout.rdbuf(); //save old buf
        std::cout.rdbuf(out.rdbuf()); //redirect std::cout to out.txt!
        myOutputGenerator.printBroken(dataJsonBroken);
        out.close();

        std::ifstream outToRead("out.txt");
        std::string line;
        int nbCharacters = 0;
        while(std::getline(outToRead, line)){
            nbCharacters += line.length();
        }
        outToRead.close();
        REQUIRE(nbCharacters>0);
    }

}

TEST_CASE("Test printIngest(dataJSON) CLI", "[UT-V-5]") {

    OutputCLI myOutputGenerator = OutputCLI::getInstance();
    REQUIRE(typeid(myOutputGenerator.getInstance()).name()=="OutputCLI");
    SECTION("is the method returning something"){
        REQUIRE(std::is_same<decltype(myOutputGenerator.printIngest(dataJsonIngest)), void>::value);
    }
    SECTION("is the  method putting something in cout"){
        std::ofstream out("out.txt"); // mettre dans dossier bin ?
        std::streambuf *coutbuf = std::cout.rdbuf(); //save old buf
        std::cout.rdbuf(out.rdbuf()); //redirect std::cout to out.txt!
        myOutputGenerator.printIngest(dataJsonIngest);
        out.close();

        std::ifstream outToRead("out.txt");
        std::string line;
        int nbCharacters = 0;
        while(std::getline(outToRead, line)){
            nbCharacters += line.length();
        }
        outToRead.close();
        REQUIRE(nbCharacters>0);
    }
}
