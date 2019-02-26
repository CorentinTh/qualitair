//
// Created by Wallyn Valentin on 17/02/2019.
//

#include "../include/Aggregation.h"
#include "../include/FormulaComputer.h"

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

    //transform sums to mean
    for (auto it = sums.begin(); it!= sums.end(); ++it) {
        //round to 2 digits
        sums[it->first] = std::floor((sums[it->first] / count[it->first]) * 100.0 + 0.5) / 100.0;
    }

    return sums;
}

std::unordered_map<std::string, std::pair<double, double>> Aggregation::computeExtrems() {
    std::unordered_map<std::string, std::pair<double, double>> results;

    for (auto i = points.begin(); i != points.end() ; ++i)
    {
        for (auto j = i->begin(); j != i->end() ; ++j)
        {
            for (auto k = j->begin(); k != j->end() ; ++k)
            {
                for (std::unordered_map<std::string, int>::const_iterator it = k->begin();
                     it != k->end(); ++it)
                {
                    //initial values
                    if (!results.count(it->first))
                    {
                        results[it->first] = std::pair<double, double>(it->second, it->second);
                    }
                    //min
                    if (it->second < results[it->first].first) {
                        results[it->first].first = it->second;
                    }
                    //max
                    if (it->second > results[it->first].second) {
                        results[it->first].second = it->second;
                    }
                }
            }
        }
    }

    return results;
}

std::unordered_map<std::string, double> Aggregation::computeDeviation() {
    std::unordered_map<std::string, double> sums;
    std::unordered_map<std::string, double> deviations;
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

    //transform sums to means
    for (auto it = sums.begin(); it!= sums.end(); ++it) {
        sums[it->first] /= count[it->first];
    }

    for (auto i = points.begin(); i != points.end() ; ++i)
    {
        for (auto j = i->begin(); j != i->end() ; ++j)
        {
            for (auto k = j->begin(); k != j->end() ; ++k)
            {
                for (std::unordered_map<std::string, int>::const_iterator it = k->begin();
                     it != k->end(); ++it)
                {
                    deviations[it->first] += std::pow(it->second - sums[it->first], 2);
                }
            }
        }
    }

    for (auto it = deviations.begin(); it!= deviations.end(); ++it) {
        deviations[it->first] = std::floor((std::sqrt(deviations[it->first] / count[it->first])) * 100.0 + 0.5) / 100.0;
    }

    return deviations;
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

json* Aggregation::apply() {
    auto avg = computeAverage();
    auto extrems = computeExtrems();
    auto deviations = computeDeviation();

    json* j = new json;

    for (auto it = deviations.begin(); it!= deviations.end(); ++it) {
        (*j)[it->first]["avg"] = avg[it->first];
        (*j)[it->first]["min"] = extrems[it->first].first;
        (*j)[it->first]["max"] = extrems[it->first].second;
        (*j)[it->first]["deviation"] = deviations[it->first];
    }

    FormulaComputer formulaComputer(formula);
    (*j)["igqa"] = formulaComputer.compute(points);

    return j;
}

void swap(Aggregation &first, Aggregation &second) {
    std::swap(first.formula, second.formula);
    std::swap(first.points, second.points);
}
