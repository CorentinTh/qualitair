//
//        ----[  QUALIT'AIR  ]----
//
//    Marsaud Menseau Thomasset Wallyn
//  Copyright © 2019 - All right reserved
//

#include <SQLiteCpp/Database.h>
#include <fstream>
#include "catch2/catch.hpp"
#include "../../../src/ETL/include/ETL.h"

#include "nlohmann/json.hpp"
#include "../../../src/Data/include/ConnectionFactory.h"
#include "../../../src/globals.h"

using json = nlohmann::json;

namespace etlTestNamespace {
    void copyFile(std::string source, std::string destination) {
        std::remove(destination.c_str());
        std::ifstream sourceStream(source, std::ios::binary);
        std::ofstream destinationStream(destination, std::ios::binary);

        destinationStream << sourceStream.rdbuf();

        sourceStream.close();
        destinationStream.close();
    }

    void initializeDatabase() {
        copyFile("../tests/data/dbmock.sqlite", "../tests/data/dbmockcopy.sqlite");
        ConnectionFactory::setDatabase("../tests/data/dbmockcopy.sqlite");
    }

    TEST_CASE("Testing ETL::ingest", "[UT-E-1]") {
        initializeDatabase();
        IETL &etl = ETL::getInstance();

        REQUIRE(etl.ingest("../tests/data/csv/clean") == 19);
        REQUIRE(etl.ingest("../tests/data/csv/dirty") == -1);
        REQUIRE(etl.ingest("../data/csv") == 0);
    }


    TEST_CASE("Testing ETL singleton", "[UT-E-2]") {
        REQUIRE(&ETL::getInstance() == &ETL::getInstance());
    }


    template<typename T>
    bool areVectorEquals(std::vector<T> *a, std::vector<T> *b) {
        if (a->size() != b->size()) return false;

        for (unsigned int i = 0; i < a->size(); ++i) {
            if (*a->at(i) != *b->at(i)) return false;
        }

        return true;
    }


    TEST_CASE("Testing ETL::getData", "[UT-E-3]") {

        SECTION("for all measures") {
            ConnectionFactory::setDatabase("../tests/data/dbmock.sqlite");

            IETL &etl = ETL::getInstance();

            std::vector<Measurement *> expected = {
                    new Measurement(1550150048, {"4", 45.7436395, 4.8801768, "Hôpital Edouard Herriot"},
                                    {"3", "mol", "Capteur en mol"}, 15),
                    new Measurement(1550150155, {"1", 45.7574995, 4.8313017, "Bellecour - Grande roue"},
                                    {"1", "mg/l", "Capteur en mg/l"}, 4),
                    new Measurement(1550150156, {"1", 45.7574995, 4.8313017, "Bellecour - Grande roue"},
                                    {"2", "%", "Capteur en pourcent"}, 5),
                    new Measurement(1550151014, {"2", 45.7632485, 4.8335574, "Cordelier - Métro"},
                                    {"3", "mol", "Capteur en mol"}, 10),
                    new Measurement(1550158000, {"2", 45.7632485, 4.8335574, "Cordelier - Métro"},
                                    {"3", "mol", "Capteur en mol"}, 28),
                    new Measurement(1550158049, {"5", 48.7138336, 2.2137995, "Polytechnique Paris Sud"},
                                    {"3", "mol", "Capteur en mol"}, 11),
            };

            auto result = (std::vector<Measurement *> *) etl.getData({{"type", ETL::MEASURE}});

            CHECK(result != nullptr);
            CHECK(!result->empty());
            CHECK(result->size() == expected.size());

            CHECK(areVectorEquals<Measurement *>(&expected, result));
        }

        SECTION("for measures by bbox") {
            ConnectionFactory::setDatabase("../tests/data/dbmock.sqlite");
            IETL &etl = ETL::getInstance();

            std::vector<Measurement *> expected = {
                    new Measurement(1550150048, {"4", 45.7436395, 4.8801768, "Hôpital Edouard Herriot"},
                                    {"3", "mol", "Capteur en mol"}, 15),
                    new Measurement(1550150155, {"1", 45.7574995, 4.8313017, "Bellecour - Grande roue"},
                                    {"1", "mg/l", "Capteur en mg/l"}, 4),
                    new Measurement(1550150156, {"1", 45.7574995, 4.8313017, "Bellecour - Grande roue"},
                                    {"2", "%", "Capteur en pourcent"}, 5),
                    new Measurement(1550151014, {"2", 45.7632485, 4.8335574, "Cordelier - Métro"},
                                    {"3", "mol", "Capteur en mol"}, 10),
                    new Measurement(1550158000, {"2", 45.7632485, 4.8335574, "Cordelier - Métro"},
                                    {"3", "mol", "Capteur en mol"}, 28),
            };

            auto result = (std::vector<Measurement *> *) etl.getData(
                    {
                            {"type",    ETL::MEASURE},
                            {"hasBBox", true},
                            {"BBox",    {
                                                {"left", 4},
                                                {"right", 5},
                                                {"top", 46},
                                                {"bottom", 45}
                                        }}
                    });

            CHECK(!result->empty());
            CHECK(result->size() == expected.size());

            CHECK(areVectorEquals<Measurement *>(&expected, result));
        }

        SECTION("for measures by start time") {
            ConnectionFactory::setDatabase("../tests/data/dbmock.sqlite");
            IETL &etl = ETL::getInstance();

            std::vector<Measurement *> expected = {
                    new Measurement(1550158000, {"2", 45.7632485, 4.8335574, "Cordelier - Métro"},
                                    {"3", "mol", "Capteur en mol"}, 28),
                    new Measurement(1550158049, {"5", 48.7138336, 2.2137995, "Polytechnique Paris Sud"},
                                    {"3", "mol", "Capteur en mol"}, 11),
            };

            auto result = (std::vector<Measurement *> *) etl.getData(
                    {
                            {"type",     ETL::MEASURE},
                            {"hasStart", true},
                            {"start",    1550157000}
                    });

            CHECK(!result->empty());
            CHECK(result->size() == expected.size());

            CHECK(areVectorEquals<Measurement *>(&expected, result));
        }

        SECTION("for measures by end time") {
            ConnectionFactory::setDatabase("../tests/data/dbmock.sqlite");
            IETL &etl = ETL::getInstance();

            std::vector<Measurement *> expected = {
                    new Measurement(1550150048, {"4", 45.7436395, 4.8801768, "Hôpital Edouard Herriot"},
                                    {"3", "mol", "Capteur en mol"}, 15),
                    new Measurement(1550150155, {"1", 45.7574995, 4.8313017, "Bellecour - Grande roue"},
                                    {"1", "mg/l", "Capteur en mg/l"}, 4),
                    new Measurement(1550150156, {"1", 45.7574995, 4.8313017, "Bellecour - Grande roue"},
                                    {"2", "%", "Capteur en pourcent"}, 5),
                    new Measurement(1550151014, {"2", 45.7632485, 4.8335574, "Cordelier - Métro"},
                                    {"3", "mol", "Capteur en mol"}, 10),
            };

            auto result = (std::vector<Measurement *> *) etl.getData(
                    {
                            {"type",   ETL::MEASURE},
                            {"hasEnd", true},
                            {"end",    1550157000}
                    });

            CHECK(!result->empty());
            CHECK(result->size() == expected.size());

            CHECK(areVectorEquals<Measurement *>(&expected, result));
        }

        SECTION("for measures by interval") {
            ConnectionFactory::setDatabase("../tests/data/dbmock.sqlite");
            IETL &etl = ETL::getInstance();

            auto result = (pointCollection *) etl.getData(
                    {
                            {"type",                 ETL::MEASURE},
                            {"hasStart",             true},
                            {"hasEnd",               true},
                            {"hasBBox",              true},
                            {"doInterpolation",      true},
                            {"start",                1550150000},
                            {"end",                  1550159000},
                            {"BBox",                 {
                                                             {"left",      4},
                                                             {"right",    5},
                                                             {"top",  46},
                                                             {"bottom", 45}
                                                     }},
                            {"spatialGranularity",   0.5},
                            {"temporalGranularity",  1000},
                            {"minimalInterDistance", {
                                                             {"longitude", 1},
                                                             {"latitude", 1},
                                                             {"time", 1000}
                                                     }}
                    });

            CHECK(!result->empty());
        }

        SECTION("for sensors") {
            ConnectionFactory::setDatabase("../tests/data/dbmock.sqlite");
            IETL &etl = ETL::getInstance();

            std::vector<Sensor *> expected = {
                    new Sensor("1", 45.7574995, 4.8313017, "Bellecour - Grande roue"),
                    new Sensor("2", 45.7632485, 4.8335574, "Cordelier - Métro"),
                    new Sensor("3", 45.7629940, 4.8336320, "Rue de la république"),
                    new Sensor("4", 45.7436395, 4.8801768, "Hôpital Edouard Herriot"),
                    new Sensor("5", 48.7138336, 2.2137995, "Polytechnique Paris Sud"),
            };

            auto result = (std::vector<Sensor *> *) etl.getData({{"type", ETL::SENSOR}});

            CHECK(!result->empty());
            CHECK(result->size() == expected.size());

            CHECK(areVectorEquals<Sensor *>(&expected, result));
        }

        SECTION("for sensors by sensorId") {
            ConnectionFactory::setDatabase("../tests/data/dbmock.sqlite");
            IETL &etl = ETL::getInstance();

            std::vector<Sensor *> expected = {
                    new Sensor("1", 45.7574995, 4.8313017, "Bellecour - Grande roue"),
            };

            auto result = (std::vector<Sensor *> *) etl.getData({
                                                                        {"type",       ETL::SENSOR},
                                                                        {"hasSensors", true},
                                                                        {"sensors",    {"1"}},
                                                                });

            CHECK(!result->empty());
            CHECK(result->size() == expected.size());

            CHECK(areVectorEquals<Sensor *>(&expected, result));
        }

        SECTION("for attributes") {
            ConnectionFactory::setDatabase("../tests/data/dbmock.sqlite");
            IETL &etl = ETL::getInstance();

            std::vector<Attribute *> expected = {
                    new Attribute("1", "mg/l", "Capteur en mg/l"),
                    new Attribute("2", "%", "Capteur en pourcent"),
                    new Attribute("3", "mol", "Capteur en mol")
            };

            auto result = (std::vector<Attribute *> *) etl.getData({{"type", ETL::ATTRIBUTE}});

            CHECK(!result->empty());
            CHECK(result->size() == expected.size());

            CHECK(areVectorEquals<Attribute *>(&expected, result));
        }

        SECTION("for attributes by attributeId") {
            ConnectionFactory::setDatabase("../tests/data/dbmock.sqlite");

            IETL &etl = ETL::getInstance();

            std::vector<Attribute *> expected = {
                    new Attribute("1", "mg/l", "Capteur en mg/l")
            };

            auto result = (std::vector<Attribute *> *) etl.getData({
                                                                           {"type",          ETL::ATTRIBUTE},
                                                                           {"hasAttributes", true},
                                                                           {"attributes",    {"1"}}
                                                                   });
            CHECK(!result->empty());
            CHECK(result->size() == expected.size());

            CHECK(areVectorEquals<Attribute *>(&expected, result));
        }
    }
}