//
// Created by Wallyn Valentin on 17/02/2019.
//

#include "../include/Measurement.h"
#include <utility>

int Measurement::getTimestamp() const {
    return timestamp;
}

double Measurement::getValue() const{
    return value;
}


Sensor Measurement::getSensor() const{
    return sensor;
}

Attribute Measurement::getAttribute() const {
    return attribute;
}

Measurement::Measurement(int t, Sensor sensor, Attribute attribute, double v) : timestamp(t), sensor(sensor), attribute(attribute), value(v) {

}

Measurement &Measurement::operator=(Measurement other) {
    swap(*this, other);
    return *this;
}

Measurement::Measurement(const Measurement &other) {
    timestamp = other.timestamp;
    value = other.value;
    sensor = other.sensor;
    attribute = other.attribute;
}

Measurement::~Measurement() {

}

bool Measurement::operator==(const Measurement &rhs) const {
    return timestamp == rhs.timestamp &&
           std::abs(value - rhs.value) < 0.00001 &&
           sensor == rhs.sensor &&
           attribute == rhs.attribute;
}

bool Measurement::operator!=(const Measurement &rhs) const {
    return !(rhs == *this);
}

void swap(Measurement & first, Measurement & second) {
    std::swap(first.timestamp, second.timestamp);
    std::swap(first.value, second.value);
    std::swap(first.attribute, second.attribute);
    std::swap(first.sensor, second.sensor);
}
