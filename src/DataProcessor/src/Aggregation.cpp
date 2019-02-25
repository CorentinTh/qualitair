//
// Created by Wallyn Valentin on 17/02/2019.
//

#include "../include/Aggregation.h"

std::unordered_map<std::string, double> Aggregation::computeAverage() {
    std::unordered_map<std::string, double> sums;
    std::unordered_map<std::string, int> count;

    for (auto i = points.begin(); i != points.end() ; ++i)
    {
        for (auto j = i->begin(); j != i->end() ; ++j)
        {
            for (auto k = j->begin(); k != j->end() ; ++k)
            {
                for (std::unordered_map<std::string, int>::const_iterator it = k->begin();
                     it != k->end(); ++it)
                {
                    sums[it->first] += it->second;
                    count[it->first]++;

                }
            }
        }
    }
    
    for (auto it = sums.begin(); it!= sums.end(); ++it) {
        sums[it->first] /= count[it->first];
    }

    return sums;
}

std::unordered_map<std::string, std::pair<double, double>> Aggregation::computeExtrems() {
    return std::unordered_map<std::string, std::pair<double, double>>();
}

std::unordered_map<std::string, double> Aggregation::computeDeviation() {
    return std::unordered_map<std::string, double>();
}

Aggregation &Aggregation::operator=(Aggregation other) {
    swap(*this, other);
    return *this;
}

Aggregation::Aggregation(const Aggregation &other) {
    formula = other.formula;
    points = other.points;
}

Aggregation::Aggregation(pointCollection & data, std::string formulaExpr) : points(data), formula(formulaExpr) {

}

Aggregation::~Aggregation() {

}

json Aggregation::apply() {

}

void swap(Aggregation &first, Aggregation &second) {
    std::swap(first.formula, second.formula);
    std::swap(first.points, second.points);
}
