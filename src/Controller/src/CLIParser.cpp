//
//        ----[  QUALIT'AIR  ]----
//
//    Marsaud Menseau Thomasset Wallyn
//  Copyright © 2019 - All right reserved
//

#include "../include/CLIParser.h"

#include <cstring>

std::string CLIParser::getArgument(std::string name, std::string defaultValue) const {
    std::string arg = parser(name).str();
    if (arg.empty()) arg = defaultValue;
    return arg;
}

std::string CLIParser::getVerb() const {
    return parser[1];
}

std::string CLIParser::getMandatoryArgument(int index) const {
    std::string result = parser[2 + index];
    if (result == "") {
        throw std::runtime_error("missing mandatory argument at index " + std::to_string(index));
    }
    return result;
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

CLIParser::CLIParser(char *const argv[]) : parser(argv) {

}

void swap(CLIParser &first, CLIParser &second) {
    std::swap(first.parser, second.parser);
}