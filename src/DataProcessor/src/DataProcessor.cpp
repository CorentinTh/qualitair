//
// Created by Wallyn Valentin on 17/02/2019.
//

#include "../include/DataProcessor.h"


json *DataProcessor::computeStats(pointCollection &data, std::string formula) {
    return nullptr;
}

json *DataProcessor::detectSimilar(std::vector<Measurement> measures, std::vector<Sensor> sensors, double epsilon,
                                   double threshold) {
    return nullptr;
}

json *DataProcessor::detectBroken(std::vector<Measurement> measures, std::vector<Sensor> sensors, int timeThreshold,
                                  std::unordered_map<std::string, std::tuple<int, int>> admissibleRanges) {
    return nullptr;
}

json *DataProcessor::detectSpikes(pointCollection &data, double valueThreshold, double areaThreshold, int delay) {
    return nullptr;
}
