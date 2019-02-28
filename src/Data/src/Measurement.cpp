//
// Created by Wallyn Valentin on 17/02/2019.
//

#include "../include/Measurement.h"
#include <utility>

int Measurement::getTimestamp() {
    return timestamp;
}

double Measurement::getValue() {
    return value;
}


Sensor Measurement::getSensor() {
    return sensor;
}

Attribute Measurement::getAttribute() {
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

void swap(Measurement & first, Measurement & second) {
    std::swap(first.timestamp, second.timestamp);
    std::swap(first.value, second.value);
    std::swap(first.attribute, second.attribute);
    std::swap(first.sensor, second.sensor);
}
