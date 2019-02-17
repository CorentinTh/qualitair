//
// Created by Wallyn Valentin on 17/02/2019.
//

#include "../include/DataProcessor.h"

void DataProcessor::computeStats(std::string formula) {

}

void DataProcessor::detectSimilar(std::vector<Measurement> measures, std::vector<Sensor> sensors, double epsilon,
                                  double threshold) {

}

void DataProcessor::detectBroken(std::vector<Measurement> measures, std::vector<Sensor> sensors, int timeThreshold,
                                 std::unordered_map<std::string, std::tuple<int, int>> admissibleRanges) {

}

void DataProcessor::detectSpikes(double valueThreshold, double areaThreshold, int delay) {

}
