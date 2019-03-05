//
// Created by vwallyn on 05/03/19.
//

#include "../include/SensorsCommand.h"

SensorsCommand &SensorsCommand::operator=(SensorsCommand other) {
    swap(*this, other);
    return *this;
}

SensorsCommand::SensorsCommand(const SensorsCommand &other) {
    bbox = other.bbox;
}

SensorsCommand::SensorsCommand(BBox b) : bbox(b) {

}

SensorsCommand::~SensorsCommand() {

}

void SensorsCommand::execute() {

}

void SensorsCommand::output() {

}

void swap(SensorsCommand &first, SensorsCommand &second) {
    std::swap(first.bbox, second.bbox);
}
