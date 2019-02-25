//
// Created by Wallyn Valentin on 17/02/2019.
//

#include "../include/Attribute.h"

std::string Attribute::getUnit() {
    return unit;
}

int Attribute::getId() {
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

Attribute::Attribute(int aId, std::string u, std::string d) : attributeId(aId), unit(u), description(d) {

}

Attribute::~Attribute() {

}

void swap(Attribute & first, Attribute & second){
    std::swap(first.unit, second.unit);
    std::swap(first.description, second.description);
    std::swap(first.attributeId, second.attributeId);
}