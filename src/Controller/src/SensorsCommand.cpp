//
// Created by vwallyn on 05/03/19.
//

#include "../include/SensorsCommand.h"
#include "../include/IngestCommand.h"

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

void to_json(json& j, const SensorsCommand& command) {
    j = json{
            {"command", "sensors"},
            {"bbox", command.bbox}
    };
}

void from_json(const json& j, SensorsCommand& command) {
    j.at("bbox").get_to(command.bbox);
}