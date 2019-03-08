#include "../include/IngestCommand.h"
#include "../../ETL/include/ETL.h"
#include "easylogging++.h"



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
    ETL etl = ETL::getInstance();

    long output = etl.ingest(input);
    if(output == 0) {
        LOG(WARNING) << "No element could not be inserted" << std::endl;
    } else if(output == -1) {
        LOG(ERROR) << "File is not properly formatted" << std::endl;
    } else {
        LOG(INFO) << output << " elements inserted successfully !";
    }
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
