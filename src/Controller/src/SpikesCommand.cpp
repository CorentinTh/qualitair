//
// Created by Wallyn Valentin on 17/02/2019.
//

#include "../include/SpikesCommand.h"

SpikesCommand &SpikesCommand::operator=(SpikesCommand other) {
    swap(*this, other);
    return *this;
}

SpikesCommand::SpikesCommand(const SpikesCommand &other) {
    attribute = other.attribute;
    bbox = other.bbox;
    start = other.start;
    end = other.end;
    sensors = other.sensors;
}

SpikesCommand::SpikesCommand(std::string attr, BBox b, time_t s, time_t e, std::vector<std::string> sen) : attribute(attr),
        bbox(b), start(s), end(s), sensors(sen)
{

}

SpikesCommand::~SpikesCommand() {

}

void SpikesCommand::execute() {

}

void SpikesCommand::output() {

}

void swap(SpikesCommand &first, SpikesCommand &second) {
    std::swap(first.bbox, second.bbox);
    std::swap(first.start, second.start);
    std::swap(first.end, second.end);
    std::swap(first.attribute, second.attribute);
    std::swap(first.sensors, second.sensors);
}

void SpikesCommand::to_json(json& j) const {
    j = json{
            {"command", "broken"},
            {"bbox", bbox},
            {"start", start},
            {"end", end},
            {"attribute", attribute},
            {"sensors", sensors}
    };
}

void SpikesCommand::from_json(const json& j) {
    j.at("bbox").get_to(bbox);
    j.at("start").get_to(start);
    j.at("end").get_to(end);
    j.at("attribute").get_to(attribute);
    j.at("sensors").get_to(sensors);
}