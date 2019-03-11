//
//        ----[  QUALIT'AIR  ]----
//
//    Marsaud Menseau Thomasset Wallyn
//  Copyright © 2019 - All right reserved
//

#include "catch2/catch.hpp"
#include <string>
#include <iostream>
#include <fstream>
#include <istream>
#include <typeinfo>

#include "../../../src/View/include/OutputHTML.h"


namespace HTMLTest {
    std::string htmlFilename = "mon_rapport_qualitair.html";
    json dataJsonSpikes = {
            {"spatialStep",  2},
            {"temporalStep", 1000},
            {"t0",           1550150155},
            {"x0",           48.8534},
            {"y0",           2.3488},
            {"pics",         {
                                     {
                                             {{{"co2", 0}}, {{"co2", 1}}},
                                             {{{"co2", 0}}, {{"co2", 0}}}
                                     },
                                     {
                                             {{{"co2", 0}}, {{"co2", 1}}},
                                             {{{"co2", 0}}, {{"co2", 0}}}
                                     }
                             }
            }
    };
    json dataJsonStats = {
            {"co2",  {
                             {"avg",        6},
                             {"min",        2},
                             {"max",        10},
                             {"deviation", 2.62}
                     }
            },
            {"o2",   {
                             {"avg",        4.88},
                             {"min",        1},
                             {"max",        10},
                             {"deviation", 2.70},
                     }
            },
            {"atmo", {
                             {"1543359600", 2},
                             {"1543446000", 3},
                             {"1543532400", 2}
                     }
            }
    };
    json dataJsonSim = {
            {
                    {
                            {"id", "sensor1"},
                            {"lat", 45.7574995},
                            {"long", 4.8313017},
                            {"description", "Bellecour - Grande roue"}
                    },
                    {
                            {"id", "sensor3"},
                            {"lat", 45.762994},
                            {"long", 4.833632},
                            {"description", "Rue de la république"}
                    }
            }
    };
    json dataJsonBroken = {
            {
                    {"start", 1550150014},
                    {"end", 1550151032},
                    {"sensor", {
                                       {"id", "sensor71"},
                                       {"lat", 48.597855},
                                       {"long", 3.401035},
                                       {"description", "Pétaouchnok"}
                               }
                    }
            },
            {
                    {"start", 1550150156},
                    {"end", 1650158000},
                    {"sensor", {
                                       {"id", "sensor147"},
                                       {"lat", 28.468412},
                                       {"long", 14.351684},
                                       {"description", "Paris - Tour Eiffel"}
                               }
                    }
            }
    };
    json dataJsonIngest = {
            {"lines_inserted", 4201},
            {"error",          ""}
    };


    TEST_CASE("Test printSpikes(dataJSON) HTML", "[UT-V-6]") {

        SECTION("is the method creating the file") {
            OutputHTML::getInstance().printSpikes(dataJsonSpikes, htmlFilename);
            std::ifstream file(htmlFilename);
            REQUIRE(file.good());
            file.close();
            remove(htmlFilename.c_str());
        }
        SECTION("is the method putting something in the html file") {
            OutputHTML::getInstance().printSpikes(dataJsonSpikes, htmlFilename);
            std::ifstream out(htmlFilename);
            std::string line;
            int nbCharacters = 0;
            while (std::getline(out, line)) {
                nbCharacters += line.length();
            }
            out.close();
            REQUIRE(nbCharacters > 0);
            remove(htmlFilename.c_str());
        }
        SECTION("is the method putting the right thing in the html file") {
            OutputHTML::getInstance().printSpikes(dataJsonSpikes, htmlFilename);

            std::ifstream out(htmlFilename);
            std::string line;
            bool titlePresent = false;
            while (std::getline(out, line)) {
                if (line.find("Spikes detection") != std::string::npos) {
                    titlePresent = true;
                }
            }
            out.close();
            REQUIRE(titlePresent);
            remove(htmlFilename.c_str());
        }
    }

    TEST_CASE("Test printStats(dataJSON) HTML", "[UT-V-7]") {

        SECTION("is the method creating the file") {
            OutputHTML::getInstance().printStats(dataJsonStats, htmlFilename);
            std::ifstream file(htmlFilename);
            REQUIRE(file.good());
            file.close();
            remove(htmlFilename.c_str());
        }
        SECTION("is the method putting something in the html file") {
            OutputHTML::getInstance().printStats(dataJsonStats, htmlFilename);
            std::ifstream out(htmlFilename);
            std::string line;
            int nbCharacters = 0;
            while (std::getline(out, line)) {
                nbCharacters += line.length();
            }
            out.close();
            REQUIRE(nbCharacters > 0);
            remove(htmlFilename.c_str());
        }
        SECTION("is the method putting the right thing in the html file") {
            OutputHTML::getInstance().printStats(dataJsonStats, htmlFilename);
            std::ifstream out(htmlFilename);
            std::string line;
            bool titlePresent = false;
            while (std::getline(out, line)) {
                if (line.find("Statistics") != std::string::npos) {
                    titlePresent = true;
                }
            }
            out.close();
            REQUIRE(titlePresent);
            remove(htmlFilename.c_str());
        }
    }

    TEST_CASE("Test printSim(dataJSON) HTML", "[UT-V-8]") {


        SECTION("is the method creating the file") {
            OutputHTML::getInstance().printSim(dataJsonSim, htmlFilename);
            std::ifstream file(htmlFilename);
            REQUIRE(file.good());
            file.close();
            remove(htmlFilename.c_str());
        }
        SECTION("is the method putting something in the html file") {
            OutputHTML::getInstance().printSim(dataJsonSim, htmlFilename);
            std::ifstream out(htmlFilename);
            std::string line;
            int nbCharacters = 0;
            while (std::getline(out, line)) {
                nbCharacters += line.length();
            }
            out.close();
            REQUIRE(nbCharacters > 0);
            remove(htmlFilename.c_str());
        }
        SECTION("is the method putting the right thing in the html file") {
            OutputHTML::getInstance().printSim(dataJsonSim, htmlFilename);
            std::ifstream out(htmlFilename);
            std::string line;
            bool titlePresent = false;
            while (std::getline(out, line)) {
                if (line.find("Similar sensors") != std::string::npos) {
                    titlePresent = true;
                }
            }
            out.close();
            REQUIRE(titlePresent);
            remove(htmlFilename.c_str());
        }
    }

    TEST_CASE("Test printBroken(dataJSON) HTML", "[UT-V-9]") {


        SECTION("is the method creating the file") {
            OutputHTML::getInstance().printBroken(dataJsonBroken, htmlFilename);
            std::ifstream file(htmlFilename);
            REQUIRE(file.good());
            file.close();
            remove(htmlFilename.c_str());
        }
        SECTION("is the method putting something in the html file") {
            OutputHTML::getInstance().printBroken(dataJsonBroken, htmlFilename);
            std::ifstream out(htmlFilename);
            std::string line;
            int nbCharacters = 0;
            while (std::getline(out, line)) {
                nbCharacters += line.length();
            }
            out.close();
            REQUIRE(nbCharacters > 0);
            remove(htmlFilename.c_str());
        }
        SECTION("is the method putting the right thing in the html file") {
            OutputHTML::getInstance().printBroken(dataJsonBroken, htmlFilename);
            std::ifstream out(htmlFilename);
            std::string line;
            bool titlePresent = false;
            while (std::getline(out, line)) {
                if (line.find("Broken sensors") != std::string::npos) {
                    titlePresent = true;
                }
            }
            out.close();
            REQUIRE(titlePresent);
            remove(htmlFilename.c_str());
        }

    }

    TEST_CASE("Test printIngest(dataJSON) HTML", "[UT-V-10]") {


        SECTION("is the method creating the file") {
            OutputHTML::getInstance().printIngest(dataJsonIngest, htmlFilename);
            std::ifstream file(htmlFilename);
            REQUIRE(file.good());
            file.close();
            remove(htmlFilename.c_str());
        }
        SECTION("is the method putting something in the html file") {
            OutputHTML::getInstance().printIngest(dataJsonIngest, htmlFilename);
            std::ifstream out(htmlFilename);
            std::string line;
            int nbCharacters = 0;
            while (std::getline(out, line)) {
                nbCharacters += line.length();
            }
            out.close();
            REQUIRE(nbCharacters > 0);
            remove(htmlFilename.c_str());
        }

        SECTION("is the method putting the right thing in the html file") {
            OutputHTML::getInstance().printIngest(dataJsonIngest, htmlFilename);
            std::ifstream out(htmlFilename);
            std::string line;
            bool titlePresent = false;
            while (std::getline(out, line)) {
                if (line.find("Ingestion") != std::string::npos) {
                    titlePresent = true;
                }
            }
            out.close();
            REQUIRE(titlePresent);
            remove(htmlFilename.c_str());
        }
    }
}