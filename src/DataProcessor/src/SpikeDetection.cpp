//
// Created by Wallyn Valentin on 17/02/2019.
//

#include "../include/SpikeDetection.h"

SpikeDetection &SpikeDetection::operator=(SpikeDetection other) {
    swap(*this, other);
    return *this;
}

SpikeDetection::SpikeDetection(const SpikeDetection &other) {
    points = other.points;
    valueThreshold = other.valueThreshold;
    areaThreshold = other.areaThreshold;
    timeThreshold = other.timeThreshold;
}

SpikeDetection::SpikeDetection(
        pointCollection * data,
        double valueThresh,
        double areaThresh,
        int timeThresh) :
        points(data), valueThreshold(valueThresh), areaThreshold(areaThresh), timeThreshold(timeThresh)
{}

SpikeDetection::~SpikeDetection() {

}

json * SpikeDetection::apply() {
    json* j = new json;
    //TODO
    return j;
}

void swap(SpikeDetection &first, SpikeDetection &second) {
    std::swap(first.points, second.points);
    std::swap(first.valueThreshold, second.valueThreshold);
    std::swap(first.areaThreshold, second.areaThreshold);
    std::swap(first.timeThreshold, second.timeThreshold);

}
