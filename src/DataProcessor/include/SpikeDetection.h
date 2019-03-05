
#ifndef QUALITAIR_SPIKEDETECTION_H
#define QUALITAIR_SPIKEDETECTION_H


#include "IDataProcess.h"
#include "../../globals.h"
#include <nlohmann/json.hpp>
#include <string>

using namespace std;
using json = nlohmann::json;

class SpikeDetection : public IDataProcess {
public:
    SpikeDetection &operator=(SpikeDetection other);

    json *apply() override;

    SpikeDetection(const SpikeDetection &other);

    SpikeDetection(pointCollection *data, double valueThreshold, unsigned int areaThreshold,
                   unsigned int timeThreshold, string attribute);

    virtual ~SpikeDetection();

    double getValue(unsigned int x, unsigned int y, unsigned int z, const string &attribute);

    bool isSpike(unsigned int x, unsigned int y, unsigned int z, const string &attribute);

    unsigned int spikeStartFrame(unsigned int x, unsigned int y, unsigned int z, const string &attribute);

protected:
    friend void swap(SpikeDetection &first, SpikeDetection &second);

    double valueThreshold;
    unsigned int areaThreshold;
    unsigned int timeThreshold;
    pointCollection *points;
    string attribute;
};


#endif //QUALITAIR_SPIKEDETECTION_H
