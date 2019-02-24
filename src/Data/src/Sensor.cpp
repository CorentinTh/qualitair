//
// Created by Wallyn Valentin on 17/02/2019.
//

#include "../include/Sensor.h"

int Sensor::getId() {
    return sensorId;
}

double Sensor::getLatitude() {
    return latitude;
}

double Sensor::getLongitude() {
    return longitude;
}

std::string Sensor::getDescription() {
    return description;
}

Sensor &Sensor::operator=(Sensor other) {
    swap(*this, other);
    return *this;
}

Sensor::Sensor(const Sensor &other) {
    sensorId = other.sensorId;
    description = other.description;
    latitude = other.latitude;
    longitude = other.longitude;
}

Sensor::Sensor() {

}

Sensor::~Sensor() {

}

void swap(Sensor & first, Sensor & second) {
    std::swap(first.sensorId, second.sensorId);
    std::swap(first.description, second.description);
    std::swap(first.longitude, second.longitude);
    std::swap(first.latitude, second.latitude);
}