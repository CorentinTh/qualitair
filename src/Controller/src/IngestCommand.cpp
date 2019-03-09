#include "../include/IngestCommand.h"
#include "../../ETL/include/ETL.h"
#include "easylogging++.h"
#include "../../View/include/OutputJSON.h"
#include "../../View/include/OutputCLI.h"
#include "../../View/include/OutputHTML.h"



IngestCommand &IngestCommand::operator=(IngestCommand other) {
    swap(*this, other);
    return *this;
}

IngestCommand::IngestCommand(const IngestCommand &other) {
    input = other.input;
}

IngestCommand::IngestCommand(std::string in, OutputArguments outputArguments) : Command(outputArguments), input(in) {

}

IngestCommand::~IngestCommand() {

}

void IngestCommand::execute() {
    IETL& etl = ETL::getInstance();

    long output = etl.ingest(input);
    json res;
    res["lines"] = output;

    if (outputArguments.outputFormat == OutputFormat::HUMAN){
        OutputCLI::getInstance().printIngest(res);
    }
    else if(outputArguments.outputFormat == OutputFormat::JSON){
        OutputJSON::getInstance().printIngest(res, outputArguments.outputFile);
    }
    else{ // OutputFormat::HTML
        OutputHTML::getInstance().printIngest(res, outputArguments.outputFile);
    }
}


void swap(IngestCommand &first, IngestCommand &second) {
    std::swap(first.input, second.input);
}

void IngestCommand::to_json(json &j) const {

}

void IngestCommand::from_json(const json &j) {

}
