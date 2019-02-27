//
// Created by Wallyn Valentin on 17/02/2019.
//

#ifndef QUALITAIR_BROKENDETECTION_H
#define QUALITAIR_BROKENDETECTION_H


#include "IDataProcess.h"
#include "../../Data/include/Sensor.h"
#include "../../Data/include/Measurement.h"
#include "../../Data/include/Attribute.h"
#include <string>
#include <unordered_map>

class BrokenDetection : IDataProcess {
    public:
        json * apply() override;

        BrokenDetection & operator = ( BrokenDetection other );
        BrokenDetection ( const BrokenDetection & other );
        BrokenDetection ( std::vector<Measurement> measures, int brokenTime,
                std::unordered_map<std::string, std::pair<int, int>> admissibleRanges);
        virtual ~BrokenDetection ( );
    
    protected:
        friend void swap(BrokenDetection & first, BrokenDetection & second);

        int brokenTime;
        std::unordered_map<std::string, std::pair<int, int>> admissibleRanges;
        std::vector<Measurement> measures;
};

//TODO move in utils file
struct pair_hash {
    template <class T>
    std::size_t operator () (const std::pair<Sensor,T> &p) const {
        auto h1 = std::hash<std::string>{}(p.first.getId());
        auto h2 = std::hash<T>{}(p.second);
        //simple
        return h1 ^ h2;
    }
};

#endif //QUALITAIR_BROKENDETECTION_H
