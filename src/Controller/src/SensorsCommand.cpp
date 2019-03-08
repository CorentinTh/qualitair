//
// Created by vwallyn on 05/03/19.
//

#include "../include/SensorsCommand.h"
#include "../../ETL/include/GeoFilter.h"
#include "../../Data/include/QueryBuilder.h"
#include "../../Data/include/ConnectionFactory.h"
#include <iostream>
#include "../../Controller/include/Config.h"

SensorsCommand &SensorsCommand::operator=(SensorsCommand other) {
    swap(*this, other);
    return *this;
}

SensorsCommand::SensorsCommand(const SensorsCommand &other) {
    bbox = other.bbox;
}


SensorsCommand::SensorsCommand(BBox b) {
    if (!b.isNull()){
        this->bbox = b;
    }
}

SensorsCommand::~SensorsCommand() {

}

void SensorsCommand::execute() {
    if(!this->bbox.isNull()){

    }
    else{

    }
}

void swap(SensorsCommand &first, SensorsCommand &second) {
    std::swap(first.bbox, second.bbox);
}

void SensorsCommand::to_json(json& j) const {
    j = json{
            {"command", "sensors"},
            {"bbox", bbox}
    };
}

void SensorsCommand::from_json(const json& j) {
    j.at("bbox").get_to(bbox);
}