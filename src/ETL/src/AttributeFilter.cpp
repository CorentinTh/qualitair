//
// Created by Wallyn Valentin on 17/02/2019.
//

#include "../include/AttributeFilter.h"
#include <algorithm>

void AttributeFilter::applyTo(QueryBuilder &qb){
    int compteur = 0;
    for (std::string attr : this->attributes){
        if (compteur == 0){
            qb.where("attributeId = ?").bind(attr);
        }
        else{
            qb.orWhere("attributeId = ?").bind(attr);
        }
        compteur++;
    }
}

void AttributeFilter::addAttribute(std::string attribute) {
    if (!attribute.empty()){
        if (std::find(this->attributes.begin(), this->attributes.end(), attribute) == this->attributes.end()){
            // if the attribute is not already in the vector
            this->attributes.push_back(attribute);
        }
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
