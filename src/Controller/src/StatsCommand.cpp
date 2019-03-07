#include "../include/StatsCommand.h"

const std::unordered_map<std::string, StatsCommand::StatEnum> StatsCommand::StatDictionary {
    {"AVG", StatsCommand::AVG}, {"EXTREMS", StatsCommand::EXTREMS}, {"DEVIATION", StatsCommand::DEVIATION}, {"ATMO", StatsCommand::ATMO}
};

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

void StatsCommand::output() {

}

void swap(StatsCommand &first, StatsCommand &second) {
    std::swap(first.type, second.type);
    std::swap(first.bbox, second.bbox);
    std::swap(first.start, second.start);
    std::swap(first.end, second.end);
    std::swap(first.attributes, second.attributes);
    std::swap(first.sensors, second.sensors);
}

void StatsCommand::to_json(json& j) const {
    j = json{
            {"command", "broken"},
            {"bbox", bbox},
            {"start", start},
            {"end", end},
            {"attribute", attributes},
            {"sensors", sensors}
    };
}

void StatsCommand::from_json(const json& j) {
    j.at("bbox").get_to(bbox);
    j.at("start").get_to(start);
    j.at("end").get_to(end);
    j.at("attribute").get_to(attributes);
    j.at("sensors").get_to(sensors);
}