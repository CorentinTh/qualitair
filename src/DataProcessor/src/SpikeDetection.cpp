//
// Created by Wallyn Valentin on 17/02/2019.
//

#include "../include/SpikeDetection.h"

SpikeDetection &SpikeDetection::operator=(SpikeDetection other) {
    return *this;
}

SpikeDetection::SpikeDetection(const SpikeDetection &other) {

}

SpikeDetection::SpikeDetection(pointCollection & data, std::string formulaExpr) : points(data), formula(formulaExpr) {

}

SpikeDetection::~SpikeDetection() {

}

json SpikeDetection::apply() {

}

void swap(SpikeDetection &first, SpikeDetection &second) {

}
