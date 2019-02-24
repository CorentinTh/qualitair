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

    // TODO check which should be real instead of integer
    databaseFilepath = reader.Get("general", "database", "");

    threshold = reader.GetInteger("similarity", "threshold", 0);
    epsilon = reader.GetInteger("similarity", "epsilon", 0);

    brokenTime = reader.GetInteger("breakdown", "brokenTime", 0);

    valueThreshold = reader.GetInteger("pics", "valueThreshold", 0);
    timeThreshold = reader.GetInteger("pics", "timeThreshold", 0);
    minimalArea = reader.GetInteger("pics", "minimalArea", 0);
    spatialGranularity = reader.GetInteger("pics", "spatialGranularity", 0);
    temporalGranularity = reader.GetInteger("pics", "temporalGranularity", 0);

    // TODO need to use this fork https://github.com/Blandinium/inih if we want the GetFields() method required by
    // admissibleRanges (we don't know the fields beforehand)
    //std::string admissibleRanges =

    igqaFormula = reader.Get("stats", "igqa", "");
}

int Config::getThreshold() {
    return threshold;
}

int Config::getEpsilon() {
    return epsilon;
}

int Config::getBrokenTime() {
    return brokenTime;
}

int Config::getValueThreshold() {
    return valueThreshold;
}

int Config::getTimeThreshold() {
    return timeThreshold;
}

int Config::getSpatialGranularity(){
    return spatialGranularity;
}

int Config::getTemporalGranularity(){
    return temporalGranularity;
}

int Config::getMinimalArea(){
    return minimalArea;
}

std::string Config::getDatabaseFilepath() {
    return databaseFilepath;
}

std::unordered_map<std::string, std::pair<int, int>> Config::getAdmissibleRanges() {
    return admissibleRanges;
}

std::string Config::getIGQAFormula() {
    return igqaFormula;
}

Config &Config::operator=(Config other) {
    swap(*this, other);
    return *this;
}

Config::Config(const Config &other) {
    databaseFilepath = other.databaseFilepath;
    igqaFormula = other.igqaFormula;
    temporalGranularity= other.temporalGranularity;
    spatialGranularity= other.spatialGranularity;
    minimalArea= other.minimalArea;
    timeThreshold= other.timeThreshold;
    valueThreshold= other.valueThreshold;
    brokenTime= other.brokenTime;
    threshold= other.threshold;
    epsilon= other.epsilon;
    admissibleRanges= other.admissibleRanges;
}

Config::Config(std::string path) : filepath(path) {

}

Config::~Config() {

}

void swap(Config &first, Config &second) {
    std::swap(first.databaseFilepath, second.databaseFilepath);
    std::swap(first.igqaFormula, second.igqaFormula);
    std::swap(first.temporalGranularity, second.temporalGranularity);
    std::swap(first.spatialGranularity, second.spatialGranularity);
    std::swap(first.minimalArea, second.minimalArea);
    std::swap(first.timeThreshold, second.timeThreshold);
    std::swap(first.valueThreshold, second.valueThreshold);
    std::swap(first.brokenTime, second.brokenTime);
    std::swap(first.threshold, second.threshold);
    std::swap(first.epsilon, second.epsilon);
    std::swap(first.admissibleRanges, second.admissibleRanges);
}

