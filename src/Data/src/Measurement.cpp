//
// Created by Wallyn Valentin on 17/02/2019.
//

#include "../include/Measurement.h"
#include <utility>

int Measurement::getTimestamp() const {
    return timestamp;
}

double Measurement::getValue() const {
    return value;
}


int Measurement::getSensorId() const {
    return sensorId;
}

int Measurement::getAttributeId() const {
    return attributeId;
}

Measurement::Measurement(int t, int sId, int aId, double v) : timestamp(t), sensorId(sId), attributeId(aId), value(v) {

}

Measurement &Measurement::operator=(Measurement other) {
    swap(*this, other);
    return *this;
}

Measurement::Measurement(const Measurement &other) {
    timestamp = other.timestamp;
    value = other.value;
    sensorId = other.sensorId;
    attributeId = other.attributeId;
}

Measurement::~Measurement() {

}

void swap(Measurement &first, Measurement &second) {
    std::swap(first.timestamp, second.timestamp);
    std::swap(first.value, second.value);
    std::swap(first.attributeId, second.attributeId);
    std::swap(first.sensorId, second.sensorId);
}
