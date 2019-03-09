//
// Created by Wallyn Valentin on 17/02/2019.
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
        int getSpatialGranularity();
        int getTemporalGranularity();
        std::unordered_map<std::string, std::pair<double ,double>> getAdmissibleRanges();
        std::string getDatabaseFilepath();

        Config & operator = ( Config other );
        Config ( const Config & other );
        explicit Config (  std::string path = FILEPATH );
        virtual ~Config ( );

    protected:
        friend void swap(Config & first, Config & second);

        double similarityThreshold;
        int brokenTime;
        double spikesValueThreshold;
        int spikesTimeThreshold;
        double spikesMinimalArea;
        int spatialGranularity;
        int temporalGranularity;
        std::unordered_map<std::string, std::pair<double,double>> admissibleRanges;
        std::string databaseFilepath;

        std::string filepath;
};


#endif //QUALITAIR_CONFIG_H
