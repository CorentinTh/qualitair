//
// Created by Wallyn Valentin on 17/02/2019.
//

#include "../include/CLIParser.h"

#include <cstring>

std::string CLIParser::getArgument(std::string name, std::string defaultValue) {
    std::string arg;
    parser(name) >> arg;

    if(arg.empty()) arg = defaultValue;
    return arg;
}

std::string CLIParser::getVerb() {
    return parser[0];
}

CLIParser &CLIParser::operator=(CLIParser other) {
    swap(*this, other);
    return *this;
}

CLIParser::CLIParser(const CLIParser &other) {
    parser = other.parser;
}

CLIParser::~CLIParser() {

}

CLIParser::CLIParser(char* const argv[]) : parser(argv){

}

void swap(CLIParser & first, CLIParser & second) {
    std::swap(first.parser, second.parser);
}