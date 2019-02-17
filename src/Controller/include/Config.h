//
// Created by Wallyn Valentin on 17/02/2019.
//

#ifndef QUALITAIR_CONFIG_H
#define QUALITAIR_CONFIG_H


#include <unordered_map>

class Config {
    public:
        void load();

        Config & operator = ( Config other );
        Config ( const Config & other );
        Config ( );
        virtual ~Config ( );

    protected:
        friend void swap(Config & first, Config & second);

        int threshold;
        int epsilon;
        int brokenTime;
        int valueThreshold;
        int timeThreshold;
        int minimalArea;
        int searchingGranularity;
        std::unordered_map<std::string, std::pair<int,int>> admissibleRanges;
        std::string igqaFormula;
};


#endif //QUALITAIR_CONFIG_H
