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
    epsilon = other.epsilon;
    threshold = other.threshold;
}

SimilarDetection::SimilarDetection(std::vector<Measurement> m, double eps,
                                   int thresh) : measures(m), epsilon(eps), threshold(thresh) {

}

SimilarDetection::~SimilarDetection() {

}

json * SimilarDetection::apply() {


    std::vector<std::pair<Sensor, Sensor>> similars;

    std::unordered_map<std::pair<Sensor, std::string>, double, pair_hash> sums;
    std::unordered_map<std::pair<Sensor, std::string>, int, pair_hash> counts;
    for (auto m : measures) {
        sums[std::make_pair(m.getSensor(), m.getAttribute().getId())] += m.getValue();
        counts[std::make_pair(m.getSensor(), m.getAttribute().getId())]++;
    }

    //transform to means
    for (auto s : sums) {
        sums[s.first] /= counts[s.first];
    }

    for (auto m : sums) {
        for (auto s : sums) {
            //compare only same attributes
            if (m.first.second == s.first.second && (((m.second - s.second) / (s.second)) * 100) > threshold) {
                similars.push_back(std::make_pair(m.first.first, s.first.first));
            }
        }
    }

    json *j = new json(similars);
    return j;
}

void swap(SimilarDetection &first, SimilarDetection &second) {
    std::swap(first.measures, second.measures);
    std::swap(first.epsilon, second.epsilon);
    std::swap(first.threshold, second.threshold);
}
