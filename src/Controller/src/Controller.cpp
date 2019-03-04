//
// Created by Wallyn Valentin on 17/02/2019.
//

#include <iomanip>
#include "../include/Controller.h"
#include "../include/StatsCommand.h"
#include "../include/CLIParser.h"
#include "../include/IngestCommand.h"
#include "../include/Config.h"

static time_t parseRFC3339Date(std::string stringDate);

Controller &Controller::operator=(Controller other) {
    return *this;
}

Controller::Controller(const Controller &other) {

}

Controller::Controller(char ** argv) {
    this->argv = argv;
}

Controller::~Controller() {

}

Command* Controller::parseCommand() {
    CLIParser cliParser(argv);

    Command * command = nullptr;
    std::string verb = cliParser.getVerb();

    if(verb == "ingest") {
        std::string input = cliParser.getArgument("input", ".");
        command = new IngestCommand(input);
    } else {
        BBox bbox(cliParser.getArgument("bbox"));
        time_t start = parseRFC3339Date(cliParser.getArgument("start"));
        time_t end = parseRFC3339Date(cliParser.getArgument("start"));
        std::vector<std::string> attributes = unjoinString(cliParser.getArgument("attributes"));
        std::vector<std::string> sensors = unjoinString(cliParser.getArgument("sensors"));

        if(verb == "stats") {

        } else if(verb == "spikes") {

        } else if(verb == "detect-broken") {

        } else if(verb == "detect-sim") {

        }

    }

    return command;
}

void Controller::execute() {
    Command * command = parseCommand();
    if(command == nullptr) {
        //TODO: log something
        exit(1);
    }

    command->execute();
    command->output();
}

time_t Controller::parseRFC3339Date(std::string stringDate) {
    std::tm date = {};
    std::istringstream stringStream(stringDate);
    stringStream >> std::get_time(&date, "%Y-%m-%d %H:%M:%S");

    if (!stringStream.fail()) {
        std::put_time(&date, "%c");
    }

    return mktime(&date);
}

std::vector<std::string> Controller::unjoinString(std::string string) {
    std::vector<std::string> values;
    size_t position = 0;
    std::string value;

    while((position = string.find(',')) != std::string::npos) {
        value = string.substr(0, position);
        values.push_back(value);
        string.erase(0, position + 1);
    }

    return values;
}