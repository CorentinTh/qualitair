

#include "../include/BrokenDetection.h"
#include "easylogging++.h"
#include <algorithm>

struct BrokenSensor {
    public:
        int start;
        int end;
        Sensor sensor;

        friend void to_json(json& j, const BrokenSensor& s);
        friend void from_json(const json& j, BrokenSensor& s);
};

void to_json(json& j, const BrokenSensor& s) {
    j = json{{"start", s.start}, {"end", s.end}, {"sensor", s.sensor}};
}

void from_json(const json& j, BrokenSensor& s) {
    j.at("start").get_to(s.start);
    j.at("end").get_to(s.end);
    j.at("sensor").get_to(s.sensor);
}

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
        std::vector<Measurement*> m,
        int bT,
        std::unordered_map<std::string, std::pair<int, int>> ranges)
        : measures(m), brokenTime(bT), admissibleRanges(ranges) {

}

BrokenDetection::~BrokenDetection() {

}



json* BrokenDetection::apply() {
    std::vector<BrokenSensor> brokenSensors;
    std::unordered_map<std::pair<Sensor, std::string>, int, utils::pair_hash> lastTimes;

    for (auto measure : measures)
    {
        auto attribute = measure->getAttribute();
        auto sensor = measure->getSensor();

        //out of admissible ranges
        if (measure->getValue() < admissibleRanges[attribute.getId()].first ||
            measure->getValue() > admissibleRanges[attribute.getId()].second) {
            auto it = find_if(brokenSensors.begin(), brokenSensors.end(), [&sensor](BrokenSensor& obj) {return obj.sensor.getId() == sensor.getId();});
            if (brokenSensors.end() != it) {
                it->end = measure->getTimestamp();
            }
            else {
                auto bs = BrokenSensor();
                bs.start = measure->getTimestamp();
                bs.end = measure->getTimestamp();
                bs.sensor = sensor;
                brokenSensors.push_back(bs);
            }
        }

        if ((measure->getTimestamp() - lastTimes[make_pair(sensor, attribute.getId())]) > brokenTime
            && lastTimes[make_pair(sensor, attribute.getId())] != 0) {
            LOG(INFO) << "Sensor " << sensor.getId() << " has no measurement for " << attribute.getId() <<
            " for more than " << brokenTime << " s" << "(" << measure->getTimestamp() << ")";

            auto it = find_if(brokenSensors.begin(), brokenSensors.end(), [&sensor](BrokenSensor& obj) {return obj.sensor.getId() == sensor.getId();});
            if (it == brokenSensors.end()) {
                auto bs = BrokenSensor();
                bs.start = lastTimes[make_pair(sensor, attribute.getId())];
                bs.end = measure->getTimestamp();
                bs.sensor = sensor;
                brokenSensors.push_back(bs);
            }
            else {
                it->end = measure->getTimestamp();
            }
        }
        lastTimes[make_pair(sensor, attribute.getId())] = measure.getTimestamp();
    }

    auto lastTimestamp = measures.back()->getTimestamp();
    for (auto lastT : lastTimes) {
        if ((lastTimestamp - lastT.second) > brokenTime) {
            auto sensor = lastT.first.first;
            auto it = find_if(brokenSensors.begin(), brokenSensors.end(), [&sensor](BrokenSensor& obj) {return obj.sensor.getId() == sensor.getId();});
            if (it == brokenSensors.end()) {
                auto bs = BrokenSensor();
                bs.start = lastT.second;
                bs.end = lastTimestamp;
                bs.sensor = sensor;
                brokenSensors.push_back(bs);
            }
        }
    }

    json* j = new json(brokenSensors);

    return j;
}

void swap(BrokenDetection &first, BrokenDetection &second) {
    std::swap(first.brokenTime, second.brokenTime);
    std::swap(first.admissibleRanges, second.admissibleRanges);
    std::swap(first.measures, second.measures);
}
