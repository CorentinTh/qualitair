//
//        ----[  QUALIT'AIR  ]----
//
//    Marsaud Menseau Thomasset Wallyn
//  Copyright © 2019 - All right reserved
//

#ifndef QUALITAIR_CONFIG_H
#define QUALITAIR_CONFIG_H

#include <unordered_map>

class Config {
public:
    static const std::string FILEPATH;

    void load();

    double getSimilarityThreshold();

    int getBrokenTime();

    double getSpikesValueThreshold();

    int getSpikesTimeThreshold();

    double getSpikesMinimalArea();

    double getSpatialGranularity();

    double getTemporalGranularity();

    std::unordered_map<std::string, std::pair<double, double>> getAdmissibleRanges();

    std::string getDatabaseFilepath();

    Config &operator=(Config other);

    Config(const Config &other);

    explicit Config(std::string path = FILEPATH);

    virtual ~Config();

protected:
    friend void swap(Config &first, Config &second);

    int brokenTime;
    int spikesTimeThreshold;
    double spatialGranularity;
    double temporalGranularity;
    std::unordered_map<std::string, std::pair<double, double>> admissibleRanges;
    std::string databaseFilepath;
    std::string filepath;
    double similarityThreshold;
    double spikesValueThreshold;
    double spikesMinimalArea;
};


#endif //QUALITAIR_CONFIG_H
