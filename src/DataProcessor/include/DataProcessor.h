//
//        ----[  QUALIT'AIR  ]----
//
//    Marsaud Menseau Thomasset Wallyn
//  Copyright © 2019 - All right reserved
//

#ifndef QUALITAIR_DATAPROCESSOR_H
#define QUALITAIR_DATAPROCESSOR_H


#include "IDataProcessor.h"

class DataProcessor : public IDataProcessor {
public:
    static IDataProcessor &getInstance() {
        static DataProcessor instance;
        return instance;
    }

    json *computeAverage(pointCollection &data) override;

    json *computeDeviation(pointCollection &data) override;

    json *computeAtmo(pointCollection &data) override;

    json *computeExtrems(pointCollection &data) override;

    json *detectSimilar(std::vector<Measurement *> measures, double threshold) override;

    json *detectBroken(std::vector<Measurement *> measures, int timeThreshold,
                       std::unordered_map<std::string, std::pair<double, double>> admissibleRanges) override;

    json *detectSpikes(pointCollection *data, std::string attribute, double valueThreshold,
                       unsigned int areaThreshold, unsigned int timeThreshold) override;


private:
    DataProcessor() = default;
};


#endif //QUALITAIR_DATAPROCESSOR_H
