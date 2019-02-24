

#include "../include/BrokenDetection.h"


BrokenDetection &BrokenDetection::operator=(BrokenDetection other) {
    return *this;
}

BrokenDetection::BrokenDetection(const BrokenDetection &other) {

}

BrokenDetection::BrokenDetection(
        std::vector<Measurement> m,
        std::vector<Sensor> s,
        int tT,
        std::unordered_map<std::string, std::pair<int, int>> ranges)
        : measures(m), sensors(s), timeThreshold(tT), admissibleRanges(ranges) {

}

BrokenDetection::~BrokenDetection() {

}

json BrokenDetection::apply() {

}

void swap(BrokenDetection &first, BrokenDetection &second) {

}
