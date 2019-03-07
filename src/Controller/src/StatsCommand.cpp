#include "../include/StatsCommand.h"


StatsCommand &StatsCommand::operator=(StatsCommand other) {
    swap(*this, other);
    return *this;
}

StatsCommand::StatsCommand(const StatsCommand &other) {
    type = other.type;
    bbox = other.bbox;
    start = other.start;
    end = other.end;
    attributes = other.attributes;
    sensors = other.sensors;
}

StatsCommand::StatsCommand(StatEnum t, BBox b, time_t s, time_t e, std::vector<std::string> attr,
                           std::vector<std::string> sen) : type(t), bbox(b), start(s), end(s), attributes(attr), sensors(sen) {

}

StatsCommand::~StatsCommand() {

}

void StatsCommand::execute() {

}

void swap(StatsCommand &first, StatsCommand &second) {
    std::swap(first.type, second.type);
    std::swap(first.bbox, second.bbox);
    std::swap(first.start, second.start);
    std::swap(first.end, second.end);
    std::swap(first.attributes, second.attributes);
    std::swap(first.sensors, second.sensors);
}

void to_json(json& j, const StatsCommand& command) {
    j = json{
            {"command", "broken"},
            {"bbox", command.bbox},
            {"start", command.start},
            {"end", command.end},
            {"attribute", command.attributes},
            {"sensors", command.sensors}
    };
}

void from_json(const json& j, StatsCommand& command) {
    j.at("bbox").get_to(command.bbox);
    j.at("start").get_to(command.start);
    j.at("end").get_to(command.end);
    j.at("attribute").get_to(command.attributes);
    j.at("sensors").get_to(command.sensors);
}