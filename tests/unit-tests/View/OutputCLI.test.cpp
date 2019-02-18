//
// Created by vwallyn on 18/02/19.
//

#include "catch2/catch.hpp"
#include <string>
#include <iostream>
#include <fstream>
#include <typeinfo>

#include "../../../src/View/include/OutputCLI.h"

string dataJsonSpikes = "{
    \"timestamp\" :  1550150155,
    \"latitude\" : 48.8534,
    \"longitude\" : 2.3488,
    \"pics\" : {
            {
                {
                    0,
                    1
                },
                {
                    0,
                    0
                }
            },
            {
                {
                    0,
                    1
                },
                {
                    0,
                    0
                }
            }
    }
};";
string dataJsonStats = "{
  \"co2\" : {
      \"avg\":6,
      \"min\":2,
      \"max\":10,
      \"deviation\":2.62
  },
  \"o2\":{
      \"avg\":4.88,
      \"min\":1,
      \"max\":10,
      \"deviation\":2.70,
  },
  \"igqa\": 0.55
};";
string dataJsonSim = "{
  {
    {
      \"id\":1,
      \"lat\":45.7574995,
      \"long\":4.8313017,
      \"description\":\"Bellecour - Grande roue\"
    },
    {
      \"id\":3,
      \"lat\":45.762994,
      \"long\":4.833632,
      \"description\":\"Rue de la république\"
    }
  }
}";
string dataJsonBroken = "{ // liste de capteurs
  { // capteur
    \"id\":71,
    \"lat\":48.597855,
    \"long\":3.401035,
    \"description\":\"Pétaouchnok\"
  },
  { // capteur
    \"id\":147,
    \"lat\":28.468412,
    \"long\":14.351684,
    \"description\":\"Paris - Tour Eiffel\"
  }
}";

TEST_CASE("Test printStats(dataJSON) CLI", "[UT-V-1]") {

    OutputCLI myOutputGenerator = OutputCLI();
    REQUIRE(typeid(myOutputGenerator.getInstance()).name()=="OutputCLI");
    SECTION("is the method returning something"){
      REQUIRE(myOutputGenerator.printSpikes(dataJsonSpikes) != 42);
    }
    SECTION("is the method putting something in cout"){
      std::ofstream out("out.txt"); // mettre dans dossier bin ?
      std::streambuf *coutbuf = std::cout.rdbuf(); //save old buf
      std::cout.rdbuf(out.rdbuf()); //redirect std::cout to out.txt!
      myOutputGenerator.printSpikes(dataJsonSpikes);
      string line;
      int nbCharacters = 0;
      while(getline(out, line)){
              nbCharacters += line.length();
      }
      out.close();
      REQUIRE(nbCharacters>0);
    }

}

TEST_CASE("Test printStats(dataJSON) CLI", "[UT-V-2]") {

    OutputCLI myOutputGenerator = OutputCLI();
    REQUIRE(typeid(myOutputGenerator.getInstance()).name()=="OutputCLI");
    SECTION("is the method returning something"){
      REQUIRE(myOutputGenerator.printStats(dataJsonStats) != 42);
    }
    SECTION("is the method putting something in cout"){
      std::ofstream out("out.txt"); // mettre dans dossier bin ?
      std::streambuf *coutbuf = std::cout.rdbuf(); //save old buf
      std::cout.rdbuf(out.rdbuf()); //redirect std::cout to out.txt!
      myOutputGenerator.printStats(dataJsonStats);
      string line;
      int nbCharacters = 0;
      while(getline(out, line)){
              nbCharacters += line.length();
      }
      out.close();
      REQUIRE(nbCharacters>0);
    }

}

TEST_CASE("Test printSim(dataJSON) CLI", "[UT-V-3]") {

    OutputCLI myOutputGenerator = OutputCLI();
    REQUIRE(typeid(myOutputGenerator.getInstance()).name()=="OutputCLI");
    SECTION("is the method returning something"){
      REQUIRE(myOutputGenerator.printSim(dataJsonSim) != 42);
    }
    SECTION("is the method putting something in cout"){
      std::ofstream out("out.txt"); // mettre dans dossier bin ?
      std::streambuf *coutbuf = std::cout.rdbuf(); //save old buf
      std::cout.rdbuf(out.rdbuf()); //redirect std::cout to out.txt!
      myOutputGenerator.printSim(dataJsonSim);
      string line;
      int nbCharacters = 0;
      while(getline(out, line)){
              nbCharacters += line.length();
      }
      out.close();
      REQUIRE(nbCharacters>0);
    }

}

TEST_CASE("Test printBroken(dataJSON) CLI", "[UT-V-4]") {

    OutputCLI myOutputGenerator = OutputCLI();
    REQUIRE(typeid(myOutputGenerator.getInstance()).name()=="OutputCLI");
    SECTION("is the method returning something"){
      REQUIRE(myOutputGenerator.printBroken(dataJsonBroken) != 42);
    }
    SECTION("is the method putting something in cout"){
      std::ofstream out("out.txt"); // mettre dans dossier bin ?
      std::streambuf *coutbuf = std::cout.rdbuf(); //save old buf
      std::cout.rdbuf(out.rdbuf()); //redirect std::cout to out.txt!
      myOutputGenerator.printBroken(dataJsonBroken);
      string line;
      int nbCharacters = 0;
      while(getline(out, line)){
              nbCharacters += line.length();
      }
      out.close();
      REQUIRE(nbCharacters>0);
    }

}

TEST_CASE("Test printIngest(dataJSON) CLI", "[UT-V-5]") {

  OutputCLI myOutputGenerator = OutputCLI();
  REQUIRE(typeid(myOutputGenerator.getInstance()).name()=="OutputCLI");

  //todo
}
