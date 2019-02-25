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
#include "../../globals.h"

#include "nlohmann/json.hpp"
using json = nlohmann::json;

class IDataProcessor {
    public:
        virtual ~IDataProcessor() {}

        virtual json computeStats(pointCollection& data, std::string formula) = 0;
        virtual json detectSimilar(std::vector<Measurement> measures, std::vector<Sensor> sensors,
                double epsilon, double threshold) = 0;
        virtual json detectBroken(std::vector<Measurement> measures, std::vector<Sensor> sensors, int timeThreshold,
                std::unordered_map<std::string, std::tuple<int,int>> admissibleRanges) = 0;
        virtual json detectSpikes(pointCollection& data, double valueThreshold, double areaThreshold, int delay) = 0;
};


#endif //QUALITAIR_IDATAPROCESSOR_H
