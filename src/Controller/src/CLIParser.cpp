//
// Created by Wallyn Valentin on 17/02/2019.
//

#include "../include/CLIParser.h"

std::string CLIParser::getArgument(std::string name) {
    return std::__cxx11::string();
}

std::string CLIParser::getVerb() {
    return std::__cxx11::string();
}

CLIParser &CLIParser::operator=(CLIParser other) {
    return *this;
}



CLIParser::CLIParser(const CLIParser &other) {

}

CLIParser::CLIParser(std::vector<std::string> arguments) : args(arguments) {

}

CLIParser::~CLIParser() {

}
