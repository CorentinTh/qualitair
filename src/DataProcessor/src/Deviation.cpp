//
//        ----[  QUALIT'AIR  ]----
//
//    Marsaud Menseau Thomasset Wallyn
//  Copyright © 2019 - All right reserved
//

#include "../include/Deviation.h"

json *Deviation::apply() {
    auto deviations = computeDeviation();
    json* j = new json(deviations);
    (*j)["dev"] = true;
    return j;
}

Deviation &Deviation::operator=(Deviation other) {
    swap(*this, other);
    return *this;
}

Deviation::Deviation(const Deviation &other) {
    points = other.points;
}

Deviation::Deviation(pointCollection &data) : points(data) {

}

Deviation::~Deviation() {

}

std::unordered_map<std::string, double> Deviation::computeDeviation() const {
    std::unordered_map<std::string, double> sums;
    std::unordered_map<std::string, double> deviations;
    std::unordered_map<std::string, int> count;

    for (auto i = points.begin(); i != points.end(); ++i) {
        for (auto j = i->begin(); j != i->end(); ++j) {
            for (auto k = j->begin(); k != j->end(); ++k) {
                for (std::unordered_map<std::string, double>::const_iterator it = k->begin();
                     it != k->end(); ++it) {
                    sums[it->first] += it->second;
                    count[it->first]++;

                }
            }
        }
    }

    //transform sums to means
    for (auto it = sums.begin(); it != sums.end(); ++it) {
        sums[it->first] /= count[it->first];
    }

    for (auto i = points.begin(); i != points.end(); ++i) {
        for (auto j = i->begin(); j != i->end(); ++j) {
            for (auto k = j->begin(); k != j->end(); ++k) {
                for (std::unordered_map<std::string, double>::const_iterator it = k->begin();
                     it != k->end(); ++it) {
                    deviations[it->first] += std::pow(it->second - sums[it->first], 2);
                }
            }
        }
    }

    for (auto it = deviations.begin(); it != deviations.end(); ++it) {
        deviations[it->first] = std::floor((std::sqrt(deviations[it->first] / count[it->first])) * 100.0 + 0.5) / 100.0;
    }

    return deviations;
}

void swap(Deviation &first, Deviation &second) {
    std::swap(first.points, second.points);
}
