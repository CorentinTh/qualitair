#define CATCH_CONFIG_MAIN   // This tells Catch to provide a main() - only do this in one cpp file

#include "catch2/catch.hpp"
#include <string>
#include <vector>
#include "../../../src/ETL/include/SensorFilter.h"
#include "../../utils.hpp"

using namespace std;

// TODO: add test id

TEST_CASE("Testing SensorFilter::addSensor", "[]") {
    SensorFilter sensorFilter1;

    vector<string> sensorsID;

    for (int i = 0; i < 10; ++i) {
        string sensorID = randomString(10);

        sensorFilter1.addSensor(sensorID);
        sensorsID.push_back(sensorID);
    }

    CHECK(sensorFilter1.apply() == "sensorID in (" + join(sensorsID) + ")" );
}

TEST_CASE("Testing SensorFilter::addSensors", "[]") {
    SensorFilter sensorFilter1;

    vector<string> sensorsID;

    for (int i = 0; i < 10; ++i) {
        string sensorID = randomString(10);

        sensorsID.push_back(sensorID);
    }
    sensorFilter1.addSensors(sensorsID);

    CHECK(sensorFilter1.apply() == "sensorID in (" + join(sensorsID) + ")" );
}



TEST_CASE("Testing TimeFilter '=' operator", "[]") {
    SensorFilter sensorFilter1, sensorFilter2;

    sensorFilter1.addSensor(randomString(10));
    sensorFilter2 = sensorFilter1;

    SECTION("Equality") {
        CHECK(sensorFilter1.apply() == sensorFilter2.apply());
    }

    sensorFilter1.addSensor(randomString(10));

    SECTION("Non-Equality") {
        CHECK(sensorFilter1.apply() != sensorFilter2.apply());
    }
}

