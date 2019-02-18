#include "../include/Config.h"
#include "INIReader.h"
#include "easylogging++.h"

#include <iostream>

const std::string Config::FILEPATH = "~/.qualitair/config.ini";

void Config::load() {
    INIReader reader(filepath);
    if (reader.ParseError() < 0) {
        LOG(ERROR) << "Unable to load " << FILEPATH << std::endl;
        return;
    }
}

int Config::getThreshold() {
    return 0;
}

int Config::getEpsilon() {
    return 0;
}

int Config::getBrokenTime() {
    return 0;
}

int Config::getValueThreshold() {
    return 0;
}

int Config::getTimeThreshold() {
    return 0;
}

int Config::getSpatialGranularity(){
    return 0;
}

int Config::getTemporalGranularity(){
    return 0;
}

int Config::getMinimalArea(){
    return 0;
}

std::unordered_map<std::string, std::pair<int, int>> Config::getAdmissibleRanges() {
    return std::unordered_map<std::string, std::pair<int, int>>();
}

std::string Config::getIGQAFormula() {
    return std::__cxx11::string();
}

Config &Config::operator=(Config other) {
    return *this;
}

Config::Config(const Config &other) {

}

Config::Config(std::string path) : filepath(path) {

}

Config::~Config() {

}

void swap(Config &first, Config &second) {

}

