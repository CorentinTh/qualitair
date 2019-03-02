//
// Created by Wallyn Valentin on 17/02/2019.
//

#include "../include/DetectSimCommand.h"

DetectSimCommand &DetectSimCommand::operator=(DetectSimCommand other) {
    return *this;
}

DetectSimCommand::DetectSimCommand(const DetectSimCommand &other) {

}

DetectSimCommand::DetectSimCommand(BBox bbox, time_t start, time_t end, std::vector<std::string> attributes, std::vector<int> sensors, double epsilon, double threshold) {

}

DetectSimCommand::~DetectSimCommand() {

}

void DetectSimCommand::execute() {

}

void DetectSimCommand::output() {

}
