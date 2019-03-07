//
// Created by Wallyn Valentin on 17/02/2019.
//

#include "../include/AttributeFilter.h"
#include <algorithm>

void AttributeFilter::applyTo(QueryBuilder &qb){
    for (std::string attr : this->attributes){
        qb.orWhere("attributeId = ?").bind(attr);
    }
}

void AttributeFilter::addAttribute(std::string attribute) {
    if (std::find(this->attributes.begin(), this->attributes.end(), attribute) == this->attributes.end()){
        // if the attribute is not already in the vector
        this->attributes.push_back(attribute);
    }
}

void AttributeFilter::addAttributes(std::vector<std::string> vectAttributes) {
    for (std::string attr : vectAttributes){
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
