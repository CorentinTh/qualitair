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

        void computeStats(std::string formula) override;

        void detectSimilar(std::vector<Measurement> measures, std::vector<Sensor> sensors, double epsilon,
                           double threshold) override;

        void detectBroken(std::vector<Measurement> measures, std::vector<Sensor> sensors, int timeThreshold,
                          std::unordered_map<std::string, std::tuple<int, int>> admissibleRanges) override;

        void detectSpikes(double valueThreshold, double areaThreshold, int delay) override;

        void operator=(DataProcessor const&)  = delete;
    
    private:
        DataProcessor() {}
};


#endif //QUALITAIR_DATAPROCESSOR_H
