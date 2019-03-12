//
//        ----[  QUALIT'AIR  ]----
//
//    Marsaud Menseau Thomasset Wallyn
//  Copyright © 2019 - All right reserved
//

#include "../include/Measurement.h"
#include <utility>

long Measurement::getTimestamp() const {
    return timestamp;
}

double Measurement::getValue() const {
    return value;
}


Sensor Measurement::getSensor() const {
    return sensor;
}

Attribute Measurement::getAttribute() const {
    return attribute;
}

Measurement::Measurement(long t, Sensor sensor, Attribute attribute, double v) : timestamp(t), sensor(sensor), attribute(attribute), value(v) {

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

void swap(Measurement &first, Measurement &second) {
    std::swap(first.timestamp, second.timestamp);
    std::swap(first.value, second.value);
    std::swap(first.attribute, second.attribute);
    std::swap(first.sensor, second.sensor);
}

void to_json(json &j, const Measurement &m) {
    j = json{{"timestamp", m.timestamp},
             {"value",     m.value},
             {"attribute", m.attribute},
             {"sensor",    m.sensor}};
}

void from_json(const json &j, Measurement &m) {
    j.at("timestamp").get_to(m.timestamp);
    j.at("value").get_to(m.value);
    j.at("attribute").get_to(m.attribute);
    j.at("sensor").get_to(m.sensor);
}