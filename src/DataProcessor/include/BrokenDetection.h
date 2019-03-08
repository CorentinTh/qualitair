//
// Created by Wallyn Valentin on 17/02/2019.
//

#ifndef QUALITAIR_BROKENDETECTION_H
#define QUALITAIR_BROKENDETECTION_H


#include "IDataProcess.h"
#include "../../Data/include/Sensor.h"
#include "../../Data/include/Measurement.h"
#include "../../Data/include/Attribute.h"
#include "../../utils.h"
#include <string>
#include <unordered_map>

class BrokenDetection : IDataProcess {
    public:
        json * apply() override;

        BrokenDetection & operator = ( BrokenDetection other );
        BrokenDetection ( const BrokenDetection & other );
        BrokenDetection ( std::vector<Measurement*> measures, int brokenTime,
                std::unordered_map<std::string, std::pair<double, double>> admissibleRanges);
        virtual ~BrokenDetection ( );
    
    protected:
        friend void swap(BrokenDetection & first, BrokenDetection & second);

        int brokenTime;
        std::unordered_map<std::string, std::pair<double, double>> admissibleRanges;
        std::vector<Measurement*> measures;
};

#endif //QUALITAIR_BROKENDETECTION_H
