//
// Created by Wallyn Valentin on 17/02/2019.
//

#include "../include/DetectSimCommand.h"

DetectSimCommand &DetectSimCommand::operator=(DetectSimCommand other) {
    swap(*this, other);
    return *this;
}

DetectSimCommand::DetectSimCommand(const DetectSimCommand &other) {
    bbox = other.bbox;
    start = other.start;
    end = other.end;
    attributes = other.attributes;
    sensors = other.sensors;
    threshold = other.threshold;
}

DetectSimCommand::DetectSimCommand(BBox b, time_t st, time_t e, std::vector<std::string> attr,
        std::vector<std::string> sen, double thresh, OutputArguments outputArguments) : Command(outputArguments), bbox(b), start(st), end(e), attributes(attr), sensors(sen),
        threshold(thresh) {
}

DetectSimCommand::~DetectSimCommand() {

}

void DetectSimCommand::execute() {

}

void DetectSimCommand::output() {

}

void swap(DetectSimCommand &first, DetectSimCommand &second) {
    std::swap(first.bbox, second.bbox);
    std::swap(first.start, second.start);
    std::swap(first.end, second.end);
    std::swap(first.attributes, second.attributes);
    std::swap(first.sensors, second.sensors);
    std::swap(first.threshold, second.threshold);
}

void DetectSimCommand::to_json(json& j) const {
    j = json{
            {"command", "similarities"},
            {"bbox", bbox},
            {"start", start},
            {"end", end},
            {"attributes", attributes},
            {"sensors", sensors},
            {"threshold", threshold}
    };
}

void DetectSimCommand::from_json(const json& j) {
    j.at("bbox").get_to(bbox);
    j.at("start").get_to(start);
    j.at("end").get_to(end);
    j.at("attributes").get_to(attributes);
    j.at("sensors").get_to(sensors);
    j.at("threshold").get_to(threshold);
}
