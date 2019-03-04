#include "../include/StatsCommand.h"


StatsCommand &StatsCommand::operator=(StatsCommand other) {
    return *this;
}

StatsCommand::StatsCommand(const StatsCommand &other) {

}

StatsCommand::StatsCommand(BBox bbox, time_t start, time_t end, std::vector<std::string> attributes, std::vector<std::string> sensors) {
    this->bbox = bbox;
    this->start = start;
    this->attributes = attributes;
    this->sensors = sensors;
}

StatsCommand::~StatsCommand() {

}

void StatsCommand::execute() {

}

void StatsCommand::output() {

}
