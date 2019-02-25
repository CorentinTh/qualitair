//
// Created by Wallyn Valentin on 17/02/2019.
//

#include "../include/SimilarDetection.h"

SimilarDetection &SimilarDetection::operator=(SimilarDetection other) {
    return *this;
}

SimilarDetection::SimilarDetection(const SimilarDetection &other) {

}

SimilarDetection::SimilarDetection(std::vector<Measurement> m, std::vector<Sensor> s, double eps,
                                   double thresh) : measures(m), sensors(s), epsilon(eps), threshold(thresh) {

}

SimilarDetection::~SimilarDetection() {

}

json SimilarDetection::apply() {

}

void swap(SimilarDetection &first, SimilarDetection &second) {

}
