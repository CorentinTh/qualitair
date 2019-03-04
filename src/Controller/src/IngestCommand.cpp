#include "../include/IngestCommand.h"


IngestCommand &IngestCommand::operator=(IngestCommand other) {
    return *this;
}

IngestCommand::IngestCommand(const IngestCommand &other) {

}

IngestCommand::IngestCommand(std::string input) {
    this->input = input;
}

IngestCommand::~IngestCommand() {

}

void IngestCommand::execute() {

}

void IngestCommand::output() {

}
