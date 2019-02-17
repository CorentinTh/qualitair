//
// Created by Wallyn Valentin on 17/02/2019.
//

#ifndef QUALITAIR_IDATAPROCESSOR_H
#define QUALITAIR_IDATAPROCESSOR_H


#include <string>
#include <vector>
#include <unordered_map>
#include "../../Data/include/Measurement.h"
#include "../../Data/include/Sensor.h"

class IDataProcessor {
    public:
        virtual ~IDataProcessor() {}
        //TODO params + return type
        virtual void computeStats(std::string formula) = 0;
        //TODO return type
        virtual void detectSimilar(std::vector<Measurement> measures, std::vector<Sensor> sensors,
                double epsilon, double threshold) = 0;
        //TODO return type
        virtual void detectBroken(std::vector<Measurement> measures, std::vector<Sensor> sensors, int timeThreshold,
                std::unordered_map<std::string, std::tuple<int,int>> admissibleRanges) = 0;
        //TODO params + return type
        virtual void detectSpikes(double valueThreshold, double areaThreshold, int delay) = 0;
};


#endif //QUALITAIR_IDATAPROCESSOR_H
