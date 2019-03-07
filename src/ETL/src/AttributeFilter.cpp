//
// Created by Wallyn Valentin on 17/02/2019.
//

#include "../include/AttributeFilter.h"
#include "../include/AttributeFilter.h"
#include <algorithm>
#include <iostream>

void AttributeFilter::applyTo(QueryBuilder &qb) {
    int compteur = 1;
    for (std::string attribute : this->attributes) {
        if (compteur == 1) {
            if (this->attributes.size() > 1) {
                qb.andWhere("(Attribute.attributeId = ?").bind(attribute);
            } else {
                qb.andWhere("Attribute.attributeId = ?").bind(attribute);
            }
        } else if (compteur == this->attributes.size()) {
            qb.orWhere("Attribute.attributeId = ?)").bind(attribute);
        } else {
            qb.orWhere("Attribute.attributeId = ?").bind(attribute);
        }
        compteur++;
    }
}

void AttributeFilter::addAttribute(std::string attribute) {
    if (std::find(this->attributes.begin(), this->attributes.end(), attribute) == this->attributes.end()) {
        // if the attribute is not already in the vector
        this->attributes.push_back(attribute);
    }
}

void AttributeFilter::addAttributes(std::vector<std::string> vectAttributes) {
    for (std::string attr : vectAttributes) {
        this->addAttribute(attr);
    }
}

AttributeFilter &AttributeFilter::operator=(AttributeFilter other) {
    return *this;
}

AttributeFilter::AttributeFilter(const AttributeFilter &other) {

}

AttributeFilter::AttributeFilter() {

}

AttributeFilter::~AttributeFilter() {

}
