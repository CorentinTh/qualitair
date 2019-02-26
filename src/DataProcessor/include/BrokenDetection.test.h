//
// Created by Wallyn Valentin on 17/02/2019.
//

#ifndef QUALITAIR_BROKENDETECTION_H
#define QUALITAIR_BROKENDETECTION_H


#include "IDataProcess.h"
#include "../../Data/include/Sensor.h"
#include "../../Data/include/Measurement.h"
#include <string>
#include <unordered_map>

class BrokenDetection : IDataProcess {
    public:
        json * apply() override;

        BrokenDetection & operator = ( BrokenDetection other );
        BrokenDetection ( const BrokenDetection & other );
        BrokenDetection ( std::vector<Measurement> measures, std::vector<Sensor> sensors, int timeThreshold,
                          std::unordered_map<std::string, std::pair<int, int>> admissibleRanges);
        virtual ~BrokenDetection ( );
    
    protected:
        friend void swap(BrokenDetection & first, BrokenDetection & second);

        int timeThreshold;
        std::unordered_map<std::string, std::pair<int, int>> admissibleRanges;
        std::vector<Measurement> measures;
        std::vector<Sensor> sensors;
};


#endif //QUALITAIR_BROKENDETECTION_H
