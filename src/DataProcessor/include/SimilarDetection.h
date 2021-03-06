//
//        ----[  QUALIT'AIR  ]----
//
//    Marsaud Menseau Thomasset Wallyn
//  Copyright © 2019 - All right reserved
//

#ifndef QUALITAIR_SIMILARDETECTION_H
#define QUALITAIR_SIMILARDETECTION_H


#include "IDataProcess.h"
#include "../../Data/include/Sensor.h"
#include "../../Data/include/Measurement.h"

class SimilarDetection : IDataProcess {
public:
    json *apply() override;

    SimilarDetection &operator=(SimilarDetection other);

    SimilarDetection(const SimilarDetection &other);

    SimilarDetection(std::vector<Measurement *> measures, double threshold);

    virtual ~SimilarDetection();

protected:
    friend void swap(SimilarDetection &first, SimilarDetection &second);

    double threshold;
    std::vector<Measurement *> measures;
};


#endif //QUALITAIR_SIMILARDETECTION_H
