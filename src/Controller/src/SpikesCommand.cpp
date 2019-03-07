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

void swap(SpikesCommand &first, SpikesCommand &second) {
    std::swap(first.bbox, second.bbox);
    std::swap(first.start, second.start);
    std::swap(first.end, second.end);
    std::swap(first.attribute, second.attribute);
    std::swap(first.sensors, second.sensors);
}

void to_json(json& j, const SpikesCommand& command) {
    j = json{
            {"command", "broken"},
            {"bbox", command.bbox},
            {"start", command.start},
            {"end", command.end},
            {"attribute", command.attribute},
            {"sensors", command.sensors}
    };
}

void from_json(const json& j, SpikesCommand& command) {
    j.at("bbox").get_to(command.bbox);
    j.at("start").get_to(command.start);
    j.at("end").get_to(command.end);
    j.at("attribute").get_to(command.attribute);
    j.at("sensors").get_to(command.sensors);
}