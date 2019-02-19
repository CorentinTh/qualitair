//
// Created by Wallyn Valentin on 17/02/2019.
//

#ifndef QUALITAIR_BROKENDETECTION_H
#define QUALITAIR_BROKENDETECTION_H


#include "IDataProcess.h"
#include <string>
#include <unordered_map>

class BrokenDetection : IDataProcess {
    public:
        json apply() override;

        BrokenDetection & operator = ( BrokenDetection other );
        BrokenDetection ( const BrokenDetection & other );
        BrokenDetection ( );
        virtual ~BrokenDetection ( );
    
    protected:
        friend void swap(BrokenDetection & first, BrokenDetection & second);

        int timeThreshold;
        std::unordered_map<std::string, std::pair<int, int>> admissibleRanges;
};


#endif //QUALITAIR_BROKENDETECTION_H
