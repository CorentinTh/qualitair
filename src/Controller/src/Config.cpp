#include "../include/Config.h"
#include "INIReader.h"
#include "easylogging++.h"
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>



#include <iostream>

const std::string Config::FILEPATH = "/.qualitair/config.ini";

void Config::load() {
    char* homeDir;
    if ((homeDir = getenv("HOME")) == NULL) {
        homeDir = getpwuid(getuid())->pw_dir;
    }
    std::string path = homeDir + filepath;
    INIReader reader(path);
    if (reader.ParseError() < 0) {
        LOG(ERROR) << "Unable to load " << path << std::endl;
        return;
    }

    databaseFilepath = reader.Get("general", "database", "");

    similarityThreshold = reader.GetInteger("similarity", "threshold", 0);

    brokenTime = (int)reader.GetInteger("breakdown", "brokenTime", 0);

    spikesValueThreshold = reader.GetReal("spikes", "valueThreshold", 0.0);
    spikesTimeThreshold = (int)reader.GetInteger("spikes", "timeThreshold", 0);
    spikesMinimalArea = reader.GetReal("spikes", "minimalArea", 0.0);

    spatialGranularity = (int)reader.GetInteger("interpolation", "spatialGranularity", 0);
    temporalGranularity = (int)reader.GetInteger("interpolation", "temporalGranularity", 0);

    try {
        std::set<std::string> fields = reader.GetFields("admissibleRanges");
        for (std::set<std::string>::iterator fieldsIt = fields.begin();
             fieldsIt != fields.end();
             fieldsIt++) {
            std::string line = reader.Get("admissibleRanges", *fieldsIt, "");
            std::string min_s = line.substr(0, line.find(":"));
            std::string max_s = line.substr(line.find(":") + 1, line.size() - line.find(":"));

            double min = std::stod(min_s);
            double max = std::stod(max_s);

            admissibleRanges[*fieldsIt] = std::make_pair(min, max);
        }
    }
    catch(std::exception const& e) {
        std::cerr << "ERREUR : " << e.what() << std::endl;
    }
}

double Config::getSimilarityThreshold() {
    return similarityThreshold;
}

int Config::getBrokenTime() {
    return brokenTime;
}

double Config::getSpikesValueThreshold() {
    return spikesValueThreshold;
}

int Config::getSpikesTimeThreshold() {
    return spikesTimeThreshold;
}

int Config::getSpatialGranularity() {
    return spatialGranularity;
}

int Config::getTemporalGranularity() {
    return temporalGranularity;
}

double Config::getSpikesMinimalArea() {
    return spikesMinimalArea;
}

std::unordered_map<std::string, std::pair<double, double>> Config::getAdmissibleRanges() {
    return admissibleRanges;
}

std::string Config::getDatabaseFilepath() {
    return databaseFilepath;
}

Config &Config::operator=(Config other) {
    swap(*this, other);
    return *this;
}

Config::Config(const Config &other) {
    databaseFilepath = other.databaseFilepath;
    temporalGranularity= other.temporalGranularity;
    spatialGranularity= other.spatialGranularity;
    spikesMinimalArea = other.spikesMinimalArea;
    spikesTimeThreshold = other.spikesTimeThreshold;
    spikesValueThreshold = other.spikesValueThreshold;
    brokenTime= other.brokenTime;
    similarityThreshold = other.similarityThreshold;
    admissibleRanges= other.admissibleRanges;
}

Config::Config(std::string path) : filepath(path) {

}

Config::~Config() {

}

void swap(Config &first, Config &second) {
    std::swap(first.databaseFilepath, second.databaseFilepath);
    std::swap(first.temporalGranularity, second.temporalGranularity);
    std::swap(first.spatialGranularity, second.spatialGranularity);
    std::swap(first.spikesMinimalArea, second.spikesMinimalArea);
    std::swap(first.spikesTimeThreshold, second.spikesTimeThreshold);
    std::swap(first.spikesValueThreshold, second.spikesValueThreshold);
    std::swap(first.brokenTime, second.brokenTime);
    std::swap(first.similarityThreshold, second.similarityThreshold);
    std::swap(first.admissibleRanges, second.admissibleRanges);
}

