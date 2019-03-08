//
// Created by Wallyn Valentin on 17/02/2019.
//

#include "../include/SensorFilter.h"
#include <algorithm>

void SensorFilter::applyTo(QueryBuilder &qb) {
    int compteur = 1;
    for (std::string sensor : this->sensors){
        if (compteur == 1){
            if (this->sensors.size()>1){
                qb.andWhere("(SensorID = ?").bind(sensor);
            }
            else{
                qb.andWhere("SensorID = ?").bind(sensor);
            }
        }
        else if(compteur == this->sensors.size()){
            qb.orWhere("SensorID = ?)").bind(sensor);
        }
        else{
            qb.orWhere("SensorID = ?").bind(sensor);
        }
        compteur++;
    }
}

void SensorFilter::addSensor(std::string sensor) {
    if (std::find(this->sensors.begin(), this->sensors.end(), sensor) == this->sensors.end()){
        // if the sensor is not already in the vector
        this->sensors.push_back(sensor);
    }
}

void SensorFilter::addSensors(std::vector<std::string> vectSensors) {
    for (std::string sensor : vectSensors) {
        this->addSensor(sensor);
    }
}

SensorFilter &SensorFilter::operator=(SensorFilter other) {
    return *this;
}

SensorFilter::SensorFilter(const SensorFilter &other) {

}

SensorFilter::SensorFilter() {

}

SensorFilter::~SensorFilter() {

}
