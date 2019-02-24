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

Measurement &Measurement::operator=(Measurement other) {
    swap(*this, other);
    return *this;
}

Measurement::Measurement(const Measurement &other) {
    timestamp = other.timestamp;
    value = other.value;
}

Measurement::Measurement() {

}

Measurement::~Measurement() {

}

void swap(Measurement & first, Measurement & second) {
    std::swap(first.timestamp, second.timestamp);
    std::swap(first.value, second.value);
}
