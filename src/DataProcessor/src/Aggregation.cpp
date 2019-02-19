//
// Created by Wallyn Valentin on 17/02/2019.
//

#include "../include/Aggregation.h"

double Aggregation::computeAverage() {
    return 0;
}

double Aggregation::computeExtrems() {
    return 0;
}

double Aggregation::computeDeviation() {
    return 0;
}

Aggregation &Aggregation::operator=(Aggregation other) {
    return *this;
}

Aggregation::Aggregation(const Aggregation &other) {

}

Aggregation::Aggregation(pointCollection & data, std::string formulaExpr) : points(data), formula(formulaExpr) {

}

Aggregation::~Aggregation() {

}

json Aggregation::apply() {

}
