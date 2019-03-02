//
// Created by Wallyn Valentin on 17/02/2019.
//

#include "../include/SpikesCommand.h"

SpikesCommand &SpikesCommand::operator=(SpikesCommand other) {
    return *this;
}

SpikesCommand::SpikesCommand(const SpikesCommand &other) {

}

SpikesCommand::SpikesCommand(BBox bbox, time_t start, time_t end, std::vector<std::string> attributes, std::vector<int> sensors) {

}

SpikesCommand::~SpikesCommand() {

}

void SpikesCommand::execute() {

}

void SpikesCommand::output() {

}
