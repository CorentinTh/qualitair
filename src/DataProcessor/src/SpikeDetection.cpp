#include <utility>
#include <iostream>

//
// Created by Wallyn Valentin on 17/02/2019.
//

#include "../include/SpikeDetection.h"

SpikeDetection &SpikeDetection::operator=(SpikeDetection other) {
    swap(*this, other);
    return *this;
}

SpikeDetection::SpikeDetection(const SpikeDetection &other) {
    points = other.points;
    valueThreshold = other.valueThreshold;
    areaThreshold = other.areaThreshold;
    timeThreshold = other.timeThreshold;
}

SpikeDetection::SpikeDetection(
        pointCollection *data,
        double valueThresh,
        unsigned int areaThresh,
        unsigned int timeThresh,
        string attribute) :
        points(data), valueThreshold(valueThresh), areaThreshold(areaThresh), timeThreshold(timeThresh), attribute(attribute) {

}

SpikeDetection::~SpikeDetection() {

}

json *SpikeDetection::apply() {
    json *j = new json;

    std::cout << valueThreshold << endl;
    std::cout << timeThreshold << endl;
    std::cout << areaThreshold << endl;

    *j = json::array();
    for (unsigned int z = 0; z < points->size(); ++z) {
        (*j)[z] = json::array();
        for (unsigned int y = 0; y < points->at(z).size(); ++y) {
            (*j)[z][y] = json::array();
            for (unsigned int x = 0; x < points->at(z)[y].size(); ++x) {
                (*j)[z][y][x] = json::array();

                for (auto &it : points->at(z)[y][x]) {
                    if (attribute == it.first){
                        (*j)[z][y][x].push_back({it.first, isSpike(x, y, z, it.first) ? 1 : 0});
                    }
                }

            }
        }
    }


    return j;
}

bool SpikeDetection::isSpike(unsigned int x, unsigned int y, unsigned int z, const string &attribute) {

    if (spikeStartFrame(x, y, z, attribute) < timeThreshold) {
        return false;
    }

    unsigned int xMax = (unsigned int) (points->at(0)[0].size());
    unsigned int yMax = (unsigned int) (points->at(0).size());
    int iMin = x - areaThreshold;
    int jMin = y - areaThreshold;
    unsigned int iMax = x + areaThreshold;
    unsigned int jMax = y + areaThreshold;

    if (iMin < 0 ||
        jMin < 0 ||
        iMax >= xMax ||
        jMax >= yMax) {
        return false;
    }


    for (unsigned int i = (unsigned int) iMin; i <= iMax; ++i) {
        for (unsigned int j = (unsigned int) jMin; j <= jMax; ++j) {
            // point in radius &&
            // point not a spike from long enough
            int distance = ((x-i) * (x-i) + (y-j) * (y-j));
            if (spikeStartFrame(i, j, z, attribute) < timeThreshold &&
                distance <= areaThreshold * areaThreshold) {
                return false;
            }
        }
    }

    return true;
}

unsigned int SpikeDetection::spikeStartFrame(unsigned int x, unsigned int y, unsigned int z, const string &attribute) {
    auto value = getValue(x, y, z, attribute);

    if (z <= 0 && value >= valueThreshold) {
        return 1;
    } else if (value >= valueThreshold) {
        return 1 + spikeStartFrame(x, y, z - 1, attribute);
    } else {
        return 0;
    }
}

double SpikeDetection::getValue(unsigned int x, unsigned int y, unsigned int z, const string &attribute) {

    auto it = points->at(z)[y][x].find(attribute);

    if (it == points->at(z)[y][x].end()) {
        throw invalid_argument("Error in spike detection: bad interpolated data.");
    }

    return it->second;
}

void swap(SpikeDetection &first, SpikeDetection &second) {
    std::swap(first.points, second.points);
    std::swap(first.valueThreshold, second.valueThreshold);
    std::swap(first.areaThreshold, second.areaThreshold);
    std::swap(first.timeThreshold, second.timeThreshold);

}
