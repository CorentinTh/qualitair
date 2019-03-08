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
        virtual json *computeAverage(pointCollection &data) = 0;
        virtual json *computeDeviation(pointCollection &data) = 0;
        virtual json *computeAtmo(pointCollection &data) = 0;
        virtual json *computeExtrems(pointCollection &data) = 0;
        virtual json *detectSimilar(std::vector<Measurement> measures, double threshold) = 0;
        virtual json *detectBroken(std::vector<Measurement> measures, int timeThreshold,
                           std::unordered_map<std::string, std::pair<int, int>> admissibleRanges) = 0;
        virtual json * detectSpikes(pointCollection *data, std::string attribute, double valueThreshold,
                            unsigned int areaThreshold, unsigned int timeThreshold) = 0;
};


#endif //QUALITAIR_IDATAPROCESSOR_H
