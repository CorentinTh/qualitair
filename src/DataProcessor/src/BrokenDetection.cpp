

#include "../include/BrokenDetection.h"
#include "easylogging++.h"
#include <algorithm>

BrokenDetection &BrokenDetection::operator=(BrokenDetection other) {
    swap(*this, other);
    return *this;
}

BrokenDetection::BrokenDetection(const BrokenDetection &other) {
    brokenTime = other.brokenTime;
    admissibleRanges = other.admissibleRanges;
    measures = other.measures;
}

BrokenDetection::BrokenDetection(
        std::vector<Measurement> m,
        int bT,
        std::unordered_map<std::string, std::pair<int, int>> ranges)
        : measures(m), brokenTime(bT), admissibleRanges(ranges) {

}

BrokenDetection::~BrokenDetection() {

}

json* BrokenDetection::apply() {
    std::vector<Sensor> brokenSensors;
    std::unordered_map<std::pair<std::string, std::string>, int, pair_hash> lastTimes;

    for (auto measure : measures)
    {
        auto attribute = measure.getAttribute();
        auto sensor = measure.getSensor();

        //out of admissible ranges
        if (measure.getValue() < admissibleRanges[attribute.getDescription()].first ||
            measure.getValue() > admissibleRanges[attribute.getDescription()].second) {

            if (brokenSensors.end() != std::find(brokenSensors.begin(), brokenSensors.end(), sensor)) {
                brokenSensors.push_back(sensor);
            }
        }

        /*if ((measure.getTimestamp() - lastTimes[make_pair(sensor.getId(), attribute.getId())]) > brokenTime
            && lastTimes[make_pair(sensor.getId(), attribute.getId())] != 0) {
            LOG(INFO) << "Sensor " << sensor.getId() << "has no measurement for " << attribute.getId() << "for more than " <<
            brokenTime;
            //TODO time unit ?

            if (std::find(brokenSensors.begin(), brokenSensors.end(), sensor)!=brokenSensors.end()) {
                brokenSensors.push_back(sensor);
            }
        }
        lastTimes[make_pair(sensor.getId(), attribute.getId())] = measure.getTimestamp();*/

    }

    json* j = new json(brokenSensors);

    return j;
}

void swap(BrokenDetection &first, BrokenDetection &second) {
    std::swap(first.brokenTime, second.brokenTime);
    std::swap(first.admissibleRanges, second.admissibleRanges);
    std::swap(first.measures, second.measures);
}
