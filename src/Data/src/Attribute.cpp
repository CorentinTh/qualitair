//
// Created by Wallyn Valentin on 17/02/2019.
//

#include "../include/Attribute.h"

std::string Attribute::getUnit() {
    return unit;
}

std::string Attribute::getId() {
    return attributeId;
}

std::string Attribute::getDescription() {
    return description;
}

Attribute &Attribute::operator=(Attribute other) {
    swap(*this, other);
    return *this;
}

Attribute::Attribute(const Attribute &other) {
    unit = other.unit;
    attributeId = other.attributeId;
    description = other.description;
}

Attribute::Attribute(std::string aId, std::string u, std::string d) : attributeId(aId), unit(u), description(d) {

}

Attribute::~Attribute() {

}

bool Attribute::operator==(const Attribute &rhs) const {
    return attributeId == rhs.attributeId &&
           unit == rhs.unit &&
           description == rhs.description;
}

bool Attribute::operator!=(const Attribute &rhs) const {
    return !(rhs == *this);
}

void swap(Attribute & first, Attribute & second){
    std::swap(first.unit, second.unit);
    std::swap(first.description, second.description);
    std::swap(first.attributeId, second.attributeId);
}