//
// Created by vwallyn on 03/03/19.
//

#include "../include/Extrems.h"

json* Extrems::apply() {
    auto extrems = computeExtrems();
    json* j = new json;
    for (auto it = extrems.begin(); it!= extrems.end(); ++it) {
        (*j)[it->first]["min"] = extrems[it->first].first;
        (*j)[it->first]["max"] = extrems[it->first].second;
    }
    return j;
}

Extrems &Extrems::operator=(Extrems other) {
    swap(*this, other);
    return *this;
}

Extrems::Extrems(const Extrems &other) {

}

Extrems::Extrems(pointCollection &data) : points(data) {

}

Extrems::~Extrems() {

}

std::unordered_map<std::string, std::pair<double, double>> Extrems::computeExtrems() const {
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

void swap(Extrems &first, Extrems &second) {
    std::swap(first.points, second.points);
}
