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

        int getThreshold();
        int getEpsilon();
        int getBrokenTime();
        int getValueThreshold();
        int getTimeThreshold();
        int getSpatialGranularity();
        int getTemporalGranularity();
        int getMinimalArea();
        std::unordered_map<std::string, std::pair<int,int>> getAdmissibleRanges();
        std::string getIGQAFormula();
        std::string getDatabaseFilepath();

        Config & operator = ( Config other );
        Config ( const Config & other );
        Config ( std::string path = FILEPATH );
        virtual ~Config ( );

    protected:
        friend void swap(Config & first, Config & second);

        int threshold;
        int epsilon;
        int brokenTime;
        int valueThreshold;
        int timeThreshold;
        int minimalArea;
        int spatialGranularity;
        int temporalGranularity;
        std::unordered_map<std::string, std::pair<int,int>> admissibleRanges;
        std::string igqaFormula;
        std::string databaseFilepath;

        std::string filepath;
};


#endif //QUALITAIR_CONFIG_H
