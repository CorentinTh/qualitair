//
// Created by Wallyn Valentin on 17/02/2019.
//

#include "../include/DetectSimCommand.h"

DetectSimCommand &DetectSimCommand::operator=(DetectSimCommand other) {
    return *this;
}

DetectSimCommand::DetectSimCommand(const DetectSimCommand &other) {

}

DetectSimCommand::DetectSimCommand(BBox bbox, time_t start, time_t end, std::vector<std::string> attributes, std::vector<std::string> sensors, double epsilon, double threshold) {
    this->bbox = bbox;
    this->start = start;
    this->attributes = attributes;
    this->sensors = sensors;
    this->epsilon = epsilon;
    this->threshold= threshold;
}

DetectSimCommand::~DetectSimCommand() {

}

void DetectSimCommand::execute() {

}

void DetectSimCommand::output() {

}
