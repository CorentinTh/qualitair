//
// Created by Wallyn Valentin on 17/02/2019.
//

#include "../include/SpikeDetection.h"

SpikeDetection &SpikeDetection::operator=(SpikeDetection other) {
    return *this;
}

SpikeDetection::SpikeDetection(const SpikeDetection &other) {

}

SpikeDetection::SpikeDetection(
        pointCollection & data,
        std::string formulaExpr,
        double valueThresh,
        double areaThresh,
        int delayValue) :
        points(data), formula(formulaExpr), valueThreshold(valueThresh), areaThreshold(areaThresh), delay(delayValue)
{}

SpikeDetection::~SpikeDetection() {

}

json * SpikeDetection::apply() {
    return nullptr;
}

void swap(SpikeDetection &first, SpikeDetection &second) {

}
