#include "catch2/catch.hpp"
#include <string>
#include <vector>
#include "../../../src/ETL/include/SensorFilter.h"

using namespace std;

TEST_CASE("Testing SensorFilter::addSensor", "[UT-E-8]") {
    SensorFilter sensorFilter;

    sensorFilter.addSensor("sensor1");
    sensorFilter.addSensor("sensor2");
    sensorFilter.addSensor("sensor3");

    CHECK(sensorFilter.apply() == "sensorID in (sensor1, sensor2, sensor3)" );
}

TEST_CASE("Testing SensorFilter::addSensors", "[UT-E-9]") {
    SensorFilter sensorFilter;

    vector<string> sensors;

    sensors.emplace_back("sensor1");
    sensors.emplace_back("sensor2");
    sensors.emplace_back("sensor3");

    sensorFilter.addSensors(sensors);

    CHECK(sensorFilter.apply() == "sensorID in (sensor1, sensor2, sensor3)" );
}

TEST_CASE("Testing TimeFilter '=' operator", "[extra]") {
    SensorFilter sensorFilter1, sensorFilter2;

    sensorFilter1.addSensor("sensor1");
    sensorFilter2 = sensorFilter1;

    SECTION("Equality") {
        CHECK(sensorFilter1.apply() == sensorFilter2.apply());
    }

    sensorFilter1.addSensor("sensor2");

    SECTION("Non-Equality") {
        CHECK(sensorFilter1.apply() != sensorFilter2.apply());
    }
}

