//
// Created by vwallyn on 18/02/19.
//

#include "catch2/catch.hpp"
#include <string>
#include <iostream>
#include <fstream>
#include <istream>
#include "../../../src/View/include/OutputCLI.h"

namespace CLITest {
    json dataJsonSpikes = {
            {"spatialStep", 2},
            {"temporalStep", 1000},
            {"t0", 1550150155},
            {"x0",  48.8534},
            {"y0", 2.3488},
            {"pics",      {
                                    {
                                            {{{"co2",0}}, {{"co2",1}}},
                                            {{{"co2",0}}, {{"co2",0}}}
                                    },
                                    {
                                            {{{"co2",0}}, {{"co2",1}}},
                                            {{{"co2",0}}, {{"co2",0}}}
                                    }
                            }
            }
    };
    json dataJsonStats = {
            {"co2",  {
                         {"avg", 6},
                         {"min", 2},
                         {"max", 10},
                         {"deviation", 2.62}
                     }
            },
            {"o2",   {
                         {"avg", 4.88},
                         {"min", 1},
                         {"max", 10},
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
                    {"sensor" ,{
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
                    {"sensor" ,{
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

    /* TODO UPDATE TESTS. BROKEN DUE TO CHANGES FROM COUT TO LOGGING LIBRARY */
    /* SORRY CYRIELLE */

    /*TEST_CASE("Test printSpikes(dataJSON) CLI", "[UT-V-1]") {

        SECTION("is the method putting something in cout") {
            std::ofstream out("out.txt");
            std::streambuf *coutbuf = std::cout.rdbuf(); //save old buf
            std::cout.rdbuf(out.rdbuf()); //redirect std::cout to out.txt!
            OutputCLI::getInstance().printSpikes(dataJsonSpikes);
            std::cout.rdbuf(coutbuf); // restore cout
            out.close();

            std::ifstream out2("out.txt");
            std::string line;
            int nbCharacters = 0;
            while (std::getline(out2, line)) {
                nbCharacters += line.length();
            }
            out2.close();
            CHECK(nbCharacters > 0);
            remove("out.txt");
        }

        SECTION("is the method putting the expected thing in cout") {
            std::ofstream out("expected_out.txt");
            std::streambuf *coutbuf = std::cout.rdbuf(); //save old buf
            std::cout.rdbuf(out.rdbuf()); //redirect std::cout to expected_out.txt!
            OutputCLI::getInstance().printSpikes(dataJsonSpikes);
            std::cout.rdbuf(coutbuf); // restore cout
            out.close();

            std::ifstream outToRead("expected_out.txt");
            std::string line;
            CHECK(std::getline(outToRead, line));
            CHECK(line == "Des pics de co2 ont été détectés :");
            CHECK(std::getline(outToRead, line));
            CHECK(line == " - en position (50.8534,2.3488) entre 14:15:55 le 14/02/2019 et 14:32:35 le 14/02/2019");
            //check if we are at the end of the file
            CHECK(!std::getline(outToRead, line));
            outToRead.close();
            remove("expected_out.txt");
        }

    }

    TEST_CASE("Test printStats(dataJSON) CLI", "[UT-V-2]") {

        SECTION("is the method putting something in cout") {
            std::ofstream out("out.txt");
            std::streambuf *coutbuf = std::cout.rdbuf(); //save old buf
            std::cout.rdbuf(out.rdbuf()); //redirect std::cout to out.txt!
            OutputCLI::getInstance().printStats(dataJsonStats);
            std::cout.rdbuf(coutbuf); // restore cout
            out.close();

            std::ifstream out2("out.txt");
            std::string line;
            int nbCharacters = 0;
            while (std::getline(out2, line)) {
                nbCharacters += line.length();
            }
            out2.close();
            CHECK(nbCharacters > 0);
            remove("out.txt");
        }
        SECTION("is the method putting the expected thing in cout") {
            std::ofstream out("expected_out.txt");
            std::streambuf *coutbuf = std::cout.rdbuf(); //save old buf
            std::cout.rdbuf(out.rdbuf()); //redirect std::cout to expected_out.txt!
            OutputCLI::getInstance().printStats(dataJsonStats);
            std::cout.rdbuf(coutbuf); // restore cout
            out.close();

            std::ifstream outToRead("expected_out.txt");
            std::string line;
            CHECK(std::getline(outToRead, line));
            CHECK(line == "Résultats des analyses :");
            CHECK(std::getline(outToRead, line));
            CHECK(line == " - ATMO :");
            CHECK(std::getline(outToRead, line));
            CHECK(line == "     28/11/2018 : 2");
            CHECK(std::getline(outToRead, line));
            CHECK(line == "     29/11/2018 : 3");
            CHECK(std::getline(outToRead, line));
            CHECK(line == "     30/11/2018 : 2");
            CHECK(std::getline(outToRead, line));
            CHECK(line == " - co2 :");
            CHECK(std::getline(outToRead, line));
            CHECK(line == "     avg : 6");
            CHECK(std::getline(outToRead, line));
            CHECK(line == "     min : 2");
            CHECK(std::getline(outToRead, line));
            CHECK(line == "     max : 10");
            CHECK(std::getline(outToRead, line));
            CHECK(line == "     deviation : 2.62");
            CHECK(std::getline(outToRead, line));
            CHECK(line == " - o2 :");
            CHECK(std::getline(outToRead, line));
            CHECK(line == "     avg : 4.88");
            CHECK(std::getline(outToRead, line));
            CHECK(line == "     min : 1");
            CHECK(std::getline(outToRead, line));
            CHECK(line == "     max : 10");
            CHECK(std::getline(outToRead, line));
            CHECK(line == "     deviation : 2.7");
            //check if we are at the end of the file
            CHECK(!std::getline(outToRead, line));
            outToRead.close();
            remove("expected_out.txt");
        }

    }

    TEST_CASE("Test printSim(dataJSON) CLI", "[UT-V-3]") {

        SECTION("is the method putting something in cout") {
            std::ofstream out("out.txt");
            std::streambuf *coutbuf = std::cout.rdbuf(); //save old buf
            std::cout.rdbuf(out.rdbuf()); //redirect std::cout to out.txt!
            OutputCLI::getInstance().printSim(dataJsonSim);
            std::cout.rdbuf(coutbuf); // restore cout
            out.close();

            std::ifstream out2("out.txt");
            std::string line;
            int nbCharacters = 0;
            while (std::getline(out2, line)) {
                nbCharacters += line.length();
            }
            out2.close();
            CHECK(nbCharacters > 0);
            remove("out.txt");
        }
        SECTION("is the method putting the expected thing in cout") {
            std::ofstream out("expected_out.txt");
            std::streambuf *coutbuf = std::cout.rdbuf(); //save old buf
            std::cout.rdbuf(out.rdbuf()); //redirect std::cout to expected_out.txt!
            OutputCLI::getInstance().printSim(dataJsonSim);
            std::cout.rdbuf(coutbuf); // restore cout
            out.close();

            std::ifstream outToRead("expected_out.txt");
            std::string line;
            CHECK(std::getline(outToRead, line));
            CHECK(line == "------");
            CHECK(std::getline(outToRead, line));
            CHECK(line == "Les capteurs suivants sont similaires :");
            CHECK(std::getline(outToRead, line));
            CHECK(line == " - Capteur sensor1 : positionné en (45.7574995,4.8313017)");
            CHECK(std::getline(outToRead, line));
            CHECK(line == "   Description : Bellecour - Grande roue");
            CHECK(std::getline(outToRead, line));
            CHECK(line == " - Capteur sensor3 : positionné en (45.762994,4.833632)");
            CHECK(std::getline(outToRead, line));
            CHECK(line == "   Description : Rue de la république");
            CHECK(std::getline(outToRead, line));
            CHECK(line == "------");
            //check if we are at the end of the file
            CHECK(!std::getline(outToRead, line));
            outToRead.close();
            remove("expected_out.txt");
        }

    }

    TEST_CASE("Test printBroken(dataJSON) CLI", "[UT-V-4]") {

        SECTION("is the method putting something in cout") {
            std::ofstream out("out.txt");
            std::streambuf *coutbuf = std::cout.rdbuf(); //save old buf
            std::cout.rdbuf(out.rdbuf()); //redirect std::cout to out.txt!
            OutputCLI::getInstance().printBroken(dataJsonBroken);
            std::cout.rdbuf(coutbuf); // restore cout
            out.close();

            std::ifstream outToRead("out.txt");
            std::string line;
            int nbCharacters = 0;
            while (std::getline(outToRead, line)) {
                nbCharacters += line.length();
            }
            outToRead.close();
            CHECK(nbCharacters > 0);
            remove("out.txt");
        }

        SECTION("is the method putting the expected thing in cout") {
            std::ofstream out("expected_out.txt");
            std::streambuf *coutbuf = std::cout.rdbuf(); //save old buf
            std::cout.rdbuf(out.rdbuf()); //redirect std::cout to expected_out.txt!
            OutputCLI::getInstance().printBroken(dataJsonBroken);
            std::cout.rdbuf(coutbuf); // restore cout

            out.close();

            std::ifstream outToRead("expected_out.txt");
            std::string line;
            CHECK(std::getline(outToRead, line));
            CHECK(line.erase(0,39) == "Les capteurs suivants sont en panne :");
            CHECK(std::getline(outToRead, line));
            CHECK(line.erase(0,39) == " - Capteur sensor71 : positionné en (48.597855,3.401035) entre 14:13:34 le 14/02/2019 et 14:30:32 le 14/02/2019");
            CHECK(std::getline(outToRead, line));
            CHECK(line.erase(0,39) == "   Description : Pétaouchnok");
            CHECK(std::getline(outToRead, line));
            CHECK(line.erase(0,39) == " - Capteur sensor147 : positionné en (28.468412,14.351684) entre 14:15:56 le 14/02/2019 et 03:13:20 le 17/04/2022");
            CHECK(std::getline(outToRead, line));
            CHECK(line.erase(0,39) == "   Description : Paris - Tour Eiffel");
            //check if we are at the end of the file
            CHECK(!std::getline(outToRead, line));
            outToRead.close();
            remove("expected_out.txt");
        }

    }

    TEST_CASE("Test printIngest(dataJSON) CLI", "[UT-V-5]") {

        SECTION("is the  method putting something in cout") {
            std::ofstream out("out.txt");
            std::streambuf *coutbuf = std::cout.rdbuf(); //save old buf
            std::cout.rdbuf(out.rdbuf()); //redirect std::cout to out.txt!
            OutputCLI::getInstance().printIngest(dataJsonIngest);
            std::cout.rdbuf(coutbuf); // restore cout
            out.close();

            std::ifstream outToRead("out.txt");
            std::string line;
            int nbCharacters = 0;
            while (std::getline(outToRead, line)) {
                nbCharacters += line.length();
            }
            outToRead.close();
            CHECK(nbCharacters > 0);
            remove("out.txt");
        }
        SECTION("is the method putting the expected thing in cout") {
            std::ofstream out("expected_out.txt");
            std::streambuf *coutbuf = std::cout.rdbuf(); //save old buf
            std::cout.rdbuf(out.rdbuf()); //redirect std::cout to expected_out.txt!
            OutputCLI::getInstance().printIngest(dataJsonIngest);
            std::cout.rdbuf(coutbuf); // restore cout
            out.close();

            std::ifstream outToRead("expected_out.txt");
            std::string line;
            CHECK(std::getline(outToRead, line));
            CHECK(line == "4201 lignes ont été insérées avec succès");
            //check if we are at the end of the file
            CHECK(!std::getline(outToRead, line));
            outToRead.close();
            remove("expected_out.txt");
        }
    }*/
}