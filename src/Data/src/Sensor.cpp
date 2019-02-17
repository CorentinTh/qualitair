//
// Created by Wallyn Valentin on 17/02/2019.
//

#include "../include/Sensor.h"

int Sensor::getId() {
    return 0;
}

double Sensor::getLatitude() {
    return 0;
}

double Sensor::getLongitude() {
    return 0;
}

std::string Sensor::getDescription() {
    return std::__cxx11::string();
}

Sensor &Sensor::operator=(Sensor other) {
    return *this;
}

Sensor::Sensor(const Sensor &other) {

}

Sensor::Sensor() {

}

Sensor::~Sensor() {

}
