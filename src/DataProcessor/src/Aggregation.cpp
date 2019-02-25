//
// Created by Wallyn Valentin on 17/02/2019.
//

#include "../include/Aggregation.h"

std::unordered_map<std::string, double> Aggregation::computeAverage() {
    return std::unordered_map<std::string, double>();
}

std::unordered_map<std::string, std::pair<double, double>> Aggregation::computeExtrems() {
    return std::unordered_map<std::string, std::pair<double, double>>();
}

std::unordered_map<std::string, double> Aggregation::computeDeviation() {
    return std::unordered_map<std::string, double>();
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

void swap(Aggregation &first, Aggregation &second) {

}
