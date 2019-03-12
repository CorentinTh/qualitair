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
    json dataJsonStatsAtmo = R"({
            "atmo": 6
    })"_json;
    json dataJsonStatsAverage = R"({"avg":true,"co2":6.0,"o2":4.88})"_json;
    json dataJsonStatsDeviation = R"({"dev":true,"co2":0.0,"o2":0.0})"_json;
    json dataJsonStatsExtrems = R"({"ext":true,"co2":{"max":4.0,"min":4.0},"o2":{"max":2.0,"min":2.0}})"_json;
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
            {"lines", 4201},
            {"error",          ""}
    };


    TEST_CASE("Test printSpikes(dataJSON) CLI", "[UT-V-1]") {

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
            CHECK(line.find("Des pics de co2 ont été détectés :")!=std::string::npos);
            CHECK(std::getline(outToRead, line));
            CHECK(line.find(" - en position (50.8534,2.3488) entre 14:15:55 le 14/02/2019 et 14:32:35 le 14/02/2019")!=std::string::npos);
            //check if we are at the end of the file
            CHECK(!std::getline(outToRead, line));
            outToRead.close();
            remove("expected_out.txt");
        }

    }

    TEST_CASE("Test printStats(dataJSON) CLI", "[UT-V-2]") {

        SECTION("is the method putting something in cout"){
            std::ofstream out("out.txt");
            std::streambuf *coutbuf = std::cout.rdbuf(); //save old buf
            std::cout.rdbuf(out.rdbuf()); //redirect std::cout to out.txt!
            SECTION("for average") {
                OutputCLI::getInstance().printStats(dataJsonStatsAverage);
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
            SECTION("for atmo") {
                OutputCLI::getInstance().printStats(dataJsonStatsAtmo);
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
            SECTION("for deviation") {
                OutputCLI::getInstance().printStats(dataJsonStatsDeviation);
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
            SECTION("for extrems") {
                OutputCLI::getInstance().printStats(dataJsonStatsExtrems);
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
        }

        SECTION("is the method putting the expected thing in cout") {
            std::ofstream out("expected_out.txt");
            std::streambuf *coutbuf = std::cout.rdbuf(); //save old buf
            std::cout.rdbuf(out.rdbuf()); //redirect std::cout to expected_out.txt!

            SECTION("for average"){
                OutputCLI::getInstance().printStats(dataJsonStatsAverage);
                std::cout.rdbuf(coutbuf); // restore cout
                out.close();

                std::ifstream outToRead("expected_out.txt");
                std::string line;
                CHECK(std::getline(outToRead, line));
                CHECK(line.find("Résultat des analyses")!=std::string::npos);
                CHECK(std::getline(outToRead, line));
                CHECK(line.find("Moyennes :")!=std::string::npos);
                CHECK(std::getline(outToRead, line));
                CHECK(line.find(" - co2 :6")!=std::string::npos);
                CHECK(std::getline(outToRead, line));
                CHECK(line.find(" - o2 :4.88")!=std::string::npos);
                //check if we are at the end of the file
                CHECK(!std::getline(outToRead, line));
                outToRead.close();
                remove("expected_out.txt");
            }
            SECTION("for atmo"){
                OutputCLI::getInstance().printStats(dataJsonStatsAtmo);
                std::cout.rdbuf(coutbuf); // restore cout
                out.close();

                std::ifstream outToRead("expected_out.txt");
                std::string line;
                CHECK(std::getline(outToRead, line));
                CHECK(line.find("Résultat des analyses")!=std::string::npos);
                CHECK(std::getline(outToRead, line));
                CHECK(line.find("ATMO : 6")!=std::string::npos);
                //check if we are at the end of the file
                CHECK(!std::getline(outToRead, line));
                outToRead.close();
                remove("expected_out.txt");
            }
            SECTION("for deviation"){
                OutputCLI::getInstance().printStats(dataJsonStatsDeviation);
                std::cout.rdbuf(coutbuf); // restore cout
                out.close();

                std::ifstream outToRead("expected_out.txt");
                std::string line;
                CHECK(std::getline(outToRead, line));
                CHECK(line.find("Résultat des analyses")!=std::string::npos);
                CHECK(std::getline(outToRead, line));
                CHECK(line.find("Ecart-types :")!=std::string::npos);
                CHECK(std::getline(outToRead, line));
                CHECK(line.find(" - co2 :0")!=std::string::npos);
                CHECK(std::getline(outToRead, line));
                CHECK(line.find(" - o2 :0")!=std::string::npos);
                //check if we are at the end of the file
                CHECK(!std::getline(outToRead, line));
                outToRead.close();
                remove("expected_out.txt");
            }
            SECTION("for extrems"){
                OutputCLI::getInstance().printStats(dataJsonStatsExtrems);
                std::cout.rdbuf(coutbuf); // restore cout
                out.close();

                std::ifstream outToRead("expected_out.txt");
                std::string line;
                CHECK(std::getline(outToRead, line));
                CHECK(line.find("Résultat des analyses")!=std::string::npos);
                CHECK(std::getline(outToRead, line));
                CHECK(line.find("Minimums et maximums :")!=std::string::npos);
                CHECK(std::getline(outToRead, line));
                CHECK(line.find(" - co2 :")!=std::string::npos);
                CHECK(std::getline(outToRead, line));
                CHECK(line.find("    min :4")!=std::string::npos);
                CHECK(std::getline(outToRead, line));
                CHECK(line.find("    max :4")!=std::string::npos);
                CHECK(std::getline(outToRead, line));
                CHECK(line.find(" - o2 :")!=std::string::npos);
                CHECK(std::getline(outToRead, line));
                CHECK(line.find("    min :2")!=std::string::npos);
                CHECK(std::getline(outToRead, line));
                CHECK(line.find("    max :2")!=std::string::npos);
                //check if we are at the end of the file
                CHECK(!std::getline(outToRead, line));
                outToRead.close();
                remove("expected_out.txt");
            }


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
            CHECK(line.find("------")!=std::string::npos);
            CHECK(std::getline(outToRead, line));
            CHECK(line.find("Les capteurs suivants sont similaires :")!=std::string::npos);
            CHECK(std::getline(outToRead, line));
            CHECK(line.find(" - Capteur sensor1 : positionné en (45.757500,4.831302)")!=std::string::npos);
            CHECK(std::getline(outToRead, line));
            CHECK(line.find("   Description : Bellecour - Grande roue")!=std::string::npos);
            CHECK(std::getline(outToRead, line));
            CHECK(line.find(" - Capteur sensor3 : positionné en (45.762994,4.833632)")!=std::string::npos);
            CHECK(std::getline(outToRead, line));
            CHECK(line.find("   Description : Rue de la république")!=std::string::npos);
            CHECK(std::getline(outToRead, line));
            CHECK(line.find("------")!=std::string::npos);
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
            CHECK(line.find("Les capteurs suivants sont en panne :")!=std::string::npos);
            CHECK(std::getline(outToRead, line));
            CHECK(line.find(" - Capteur sensor71 : positionné en (48.597855,3.401035) entre 14:13:34 le 14/02/2019 et 14:30:32 le 14/02/2019")!=std::string::npos);
            CHECK(std::getline(outToRead, line));
            CHECK(line.find("   Description : Pétaouchnok")!=std::string::npos);
            CHECK(std::getline(outToRead, line));
            CHECK(line.find(" - Capteur sensor147 : positionné en (28.468412,14.351684) entre 14:15:56 le 14/02/2019 et 03:13:20 le 17/04/2022")!=std::string::npos);
            CHECK(std::getline(outToRead, line));
            CHECK(line.find("   Description : Paris - Tour Eiffel")!=std::string::npos);
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
            CHECK(line.find("4201 elements inserted successfully !")!=std::string::npos);
            //check if we are at the end of the file
            CHECK(!std::getline(outToRead, line));
            outToRead.close();
            remove("expected_out.txt");
        }
    }
}