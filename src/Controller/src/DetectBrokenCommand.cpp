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

void DetectBrokenCommand::to_json(json& j) const {
    j = json{
        {"command", "broken"},
        {"bbox", bbox},
        {"start", start},
        {"end", end},
        {"attributes", attributes},
        {"sensors", sensors}
    };
}

void DetectBrokenCommand::from_json(const json& j) {
    j.at("bbox").get_to(bbox);
    j.at("start").get_to(start);
    j.at("end").get_to(end);
    j.at("attributes").get_to(attributes);
    j.at("sensors").get_to(sensors);
}