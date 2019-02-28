//
// Created by Wallyn Valentin on 17/02/2019.
//

#include "../include/Sensor.h"

std::string Sensor::getId() const {
    return sensorId;
}

double Sensor::getLatitude() const{
    return latitude;
}

double Sensor::getLongitude() const{
    return longitude;
}

std::string Sensor::getDescription() const {
    return description;
}

Sensor &Sensor::operator=(Sensor other) {
    swap(*this, other);
    return *this;
}

bool Sensor::operator==(const Sensor &rhs) const {
    return rhs.sensorId == sensorId &&
           rhs.latitude == latitude &&
           rhs.longitude == longitude &&
           rhs.description == description;
}

Sensor::Sensor(const Sensor &other) {
    sensorId = other.sensorId;
    description = other.description;
    latitude = other.latitude;
    longitude = other.longitude;
}

Sensor::Sensor(std::string sId, double lat, double lon, std::string d) : sensorId(sId), latitude(lat), longitude(lon), description(d) {

}

Sensor::~Sensor() {

}

void swap(Sensor & first, Sensor & second) {
    std::swap(first.sensorId, second.sensorId);
    std::swap(first.description, second.description);
    std::swap(first.longitude, second.longitude);
    std::swap(first.latitude, second.latitude);
}

void to_json(json& j, const Sensor& s) {
    j = json{{"id", s.sensorId}, {"long", s.longitude}, {"lat", s.latitude}, {"description", s.description}};
}

void from_json(const json& j, Sensor& s) {
    j.at("description").get_to(s.description);
    j.at("id").get_to(s.sensorId);
    j.at("long").get_to(s.longitude);
    j.at("lat").get_to(s.latitude);
}