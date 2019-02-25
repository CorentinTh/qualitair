//
// Created by Wallyn Valentin on 17/02/2019.
//

#ifndef QUALITAIR_DATAPROCESSOR_H
#define QUALITAIR_DATAPROCESSOR_H


#include "IDataProcessor.h"

class DataProcessor : public IDataProcessor {
    public:
        static DataProcessor& getInstance()
        {
            static DataProcessor instance;
            return instance;
        }

        DataProcessor(DataProcessor const&)       = delete;

        json computeStats(pointCollection &data, std::string formula) override;

        json detectSimilar(std::vector<Measurement> measures, std::vector<Sensor> sensors, double epsilon,
                           double threshold) override;

        json detectBroken(std::vector<Measurement> measures, std::vector<Sensor> sensors, int timeThreshold,
                          std::unordered_map<std::string, std::tuple<int, int>> admissibleRanges) override;

        json detectSpikes(pointCollection &data, double valueThreshold, double areaThreshold, int delay) override;


    private:
        DataProcessor() {}
};


#endif //QUALITAIR_DATAPROCESSOR_H
