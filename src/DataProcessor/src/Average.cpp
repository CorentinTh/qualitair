//
//        ----[  QUALIT'AIR  ]----
//
//    Marsaud Menseau Thomasset Wallyn
//  Copyright © 2019 - All right reserved
//

#include "../include/Average.h"

json *Average::apply() {
    auto means = computeAverage();
    json *j = new json(means);
    return j;
}

Average &Average::operator=(Average other) {
    swap(*this, other);
    return *this;
}

Average::Average(const Average &other) {
    points = other.points;
}

Average::Average(pointCollection &data) : points(data) {

}

Average::~Average() {

}

std::unordered_map<std::string, double> Average::computeAverage() const {
    std::unordered_map<std::string, double> sums;
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

    //transform sums to mean
    for (auto it = sums.begin(); it != sums.end(); ++it) {
        //round to 2 digits
        sums[it->first] = std::floor((sums[it->first] / count[it->first]) * 100.0 + 0.5) / 100.0;
    }

    return sums;
}

void swap(Average &first, Average &second) {
    std::swap(first.points, second.points);
}
