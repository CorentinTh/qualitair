#include "../include/StatsCommand.h"


StatsCommand &StatsCommand::operator=(StatsCommand other) {
    return *this;
}

StatsCommand::StatsCommand(const StatsCommand &other) {

}

StatsCommand::StatsCommand(BBox bbox, time_t start, time_t end, std::vector<std::string> attributes, std::vector<int> sensors) {

}

StatsCommand::~StatsCommand() {

}

void StatsCommand::execute() {

}

void StatsCommand::output() {

}
