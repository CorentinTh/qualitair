//
// Created by Wallyn Valentin on 17/02/2019.
//

#include "../include/DetectBrokenCommand.h"

DetectBrokenCommand &DetectBrokenCommand::operator=(DetectBrokenCommand other) {
    swap(*this, other);
    return *this;
}

void DetectBrokenCommand::execute() {

}

void DetectBrokenCommand::output() {

}

DetectBrokenCommand::DetectBrokenCommand(const DetectBrokenCommand &other) {
    bbox = other.bbox;
    start = other.start;
    end = other.end;
    attributes = other.attributes;
    sensors = other.sensors;
}

DetectBrokenCommand::DetectBrokenCommand(BBox box, time_t st, time_t e, std::vector<std::string> attr,
        std::vector<std::string> sens) : bbox(box), start(st), end(e), attributes(attr), sensors(sens)
{

}

DetectBrokenCommand::~DetectBrokenCommand() {

}

void swap(DetectBrokenCommand &first, DetectBrokenCommand &second) {
    std::swap(first.bbox, second.bbox);
    std::swap(first.start, second.start);
    std::swap(first.end, second.end);
    std::swap(first.attributes, second.attributes);
    std::swap(first.sensors, second.sensors);
}

void to_json(json& j, const DetectBrokenCommand& command) {
    j = json{
        {"command", "broken"},
        {"bbox", command.bbox},
        {"start", command.start},
        {"end", command.end},
        {"attributes", command.attributes},
        {"sensors", command.sensors}
    };
}

void from_json(const json& j, DetectBrokenCommand& command) {
    j.at("bbox").get_to(command.bbox);
    j.at("start").get_to(command.start);
    j.at("end").get_to(command.end);
    j.at("attributes").get_to(command.attributes);
    j.at("sensors").get_to(command.sensors);
}