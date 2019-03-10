//
// Created by Wallyn Valentin on 17/02/2019.
//

#include "../include/SimilarDetection.h"
#include "../include/BrokenDetection.h"

SimilarDetection &SimilarDetection::operator=(SimilarDetection other) {
    swap(*this, other);
    return *this;
}

SimilarDetection::SimilarDetection(const SimilarDetection &other) {
    measures = other.measures;
    threshold = other.threshold;
}

SimilarDetection::SimilarDetection(std::vector<Measurement*> m, double thresh) : measures(m), threshold(thresh) {

}

SimilarDetection::~SimilarDetection() {

}

json * SimilarDetection::apply() {
    std::unordered_map<std::string, std::vector<std::vector<Sensor>>> results;

    std::unordered_map<std::pair<Sensor, std::string>, double, utils::pair_hash> sums;
    std::unordered_map<std::pair<Sensor, std::string>, int, utils::pair_hash> counts;
    for (auto m : measures) {
        sums[std::make_pair(m->getSensor(), m->getAttribute().getId())] += m->getValue();
        counts[std::make_pair(m->getSensor(), m->getAttribute().getId())]++;
    }

    //transform to means
    for (auto s : sums) {
        sums[s.first] /= counts[s.first];
    }

    for (auto m : sums) {
        for (auto s : sums) {
            //compare only same attributes
            if (m.first.second == s.first.second && !(m.first.first == s.first.first)) {
                double diff = std::abs((((std::max(m.second, s.second) - std::min(m.second, s.second)) / (std::max(m.second, s.second) )) * 100));

                if (diff < threshold) {
                    bool existing = false;
                    for (int i = 0; i < results[m.first.second].size(); i++) {
                        std::vector<Sensor> vec = results[m.first.second][i];
                        //if m is in that list
                        if (std::find(vec.begin(), vec.end(), m.first.first) != vec.end()) {
                            existing = true;
                            // and not s
                            if (std::find(vec.begin(), vec.end(), s.first.first) == vec.end()) {
                                //then add s as well
                                results[m.first.second][i].push_back(s.first.first);

                            }
                        }
                        //if s is in that list
                        else if (std::find(vec.begin(), vec.end(), s.first.first) != vec.end()) {
                            existing = true;
                            // and not m
                            if (std::find(vec.begin(), vec.end(), m.first.first) == vec.end()) {
                                //then add m as well
                                results[m.first.second][i].push_back(m.first.first);
                            }
                        }
                    }
                    if (!existing) {
                        //if not in existing list, create a new similarity list
                        results[m.first.second].push_back(std::vector<Sensor>{m.first.first, s.first.first});
                    }
                }
            }
        }
    }

    json* j = new json(results);

    return j;
}

void swap(SimilarDetection &first, SimilarDetection &second) {
    std::swap(first.measures, second.measures);
    std::swap(first.threshold, second.threshold);
}
