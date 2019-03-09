//
// Created by Wallyn Valentin on 17/02/2019.
//

#include "../include/AttributeFilter.h"
#include <algorithm>

void AttributeFilter::applyTo(QueryBuilder &qb){
    int compteur = 1;
    for (std::string attr : this->attributes){
        if (compteur == 1){
            if (this->attributes.size()>1){
                qb.andWhere("(AttributeID = ?").bind(attr);
            }
            else{
                qb.andWhere("AttributeID = ?").bind(attr);
            }
        }
        else if(compteur == this->attributes.size()){
            qb.orWhere("AttributeID = ?)").bind(attr);
        }
        else{
            qb.orWhere("AttributeID = ?").bind(attr);
        }
        compteur++;
    }
}

void AttributeFilter::addAttribute(std::string attribute) {
    if (!attribute.empty()){
        if (std::find(attributes.begin(), attributes.end(), attribute) == attributes.end()){
            // if the attribute is not already in the vector
            attributes.push_back(attribute);
        }
    }
}

void AttributeFilter::addAttributes(std::vector<std::string> vectAttributes) {
    for (std::string attr : vectAttributes) {
        addAttribute(attr);
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
