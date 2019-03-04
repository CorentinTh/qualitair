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
    } else if(verb == "stats") {

    } else if(verb == "spikes") {

    } else if(verb == "detect-broken") {

    } else if(verb == "detect-sim") {

    }

    return command;
}

void Controller::execute() {
    Command * command = parseCommand();
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