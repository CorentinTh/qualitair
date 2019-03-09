//
// Created by Wallyn Valentin on 17/02/2019.
//

#include "../include/DataProcessor.h"
#include "../include/Average.h"
#include "../include/Deviation.h"
#include "../include/ATMOComputer.h"
#include "../include/Extrems.h"
#include "../include/SimilarDetection.h"
#include "../include/BrokenDetection.h"
#include "../include/SpikeDetection.h"


json *DataProcessor::detectSpikes(pointCollection *data, std::string attribute, double valueThreshold,
        unsigned int areaThreshold, unsigned int timeThreshold) {
     return SpikeDetection(data, valueThreshold, areaThreshold, timeThreshold, attribute).apply();
}

json *DataProcessor::computeAverage(pointCollection &data) {
    return Average(data).apply();
}

json *DataProcessor::computeDeviation(pointCollection &data) {
    return Deviation(data).apply();
}

json *DataProcessor::computeAtmo(pointCollection &data) {
    return ATMOComputer(data).apply();
}

json *DataProcessor::computeExtrems(pointCollection &data) {
    return Extrems(data).apply();
}

json *DataProcessor::detectSimilar(std::vector<Measurement> measures, double threshold) {
    return SimilarDetection(measures, threshold).apply();
}

json *DataProcessor::detectBroken(std::vector<Measurement> measures, int timeThreshold,
                                  std::unordered_map<std::string, std::pair<int, int>> admissibleRanges) {
    return BrokenDetection(measures, timeThreshold, admissibleRanges).apply();
}
