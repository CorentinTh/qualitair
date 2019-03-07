#include "../include/IngestCommand.h"


IngestCommand &IngestCommand::operator=(IngestCommand other) {
    swap(*this, other);
    return *this;
}

IngestCommand::IngestCommand(const IngestCommand &other) {
    input = other.input;
}

IngestCommand::IngestCommand(std::string in) : input(in) {

}

IngestCommand::~IngestCommand() {

}

void IngestCommand::execute() {

}

void IngestCommand::output() {

}

void swap(IngestCommand &first, IngestCommand &second) {
    std::swap(first.input, second.input);
}

void IngestCommand::to_json(json &j) const {

}

void IngestCommand::from_json(const json &j) {

}
