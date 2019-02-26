//
// Created by Wallyn Valentin on 17/02/2019.
//

#ifndef QUALITAIR_SIMILARDETECTION_H
#define QUALITAIR_SIMILARDETECTION_H


#include "IDataProcess.h"
#include "../../Data/include/Sensor.h"
#include "../../Data/include/Measurement.h"

class SimilarDetection : IDataProcess {
    public:
        json* apply() override;

        SimilarDetection & operator = ( SimilarDetection other );
        SimilarDetection ( const SimilarDetection & other );
        SimilarDetection ( std::vector<Measurement> measures, std::vector<Sensor> sensors, double epsilon,
                           double threshold);
        virtual ~SimilarDetection ( );
    
    protected:
        friend void swap(SimilarDetection & first, SimilarDetection & second);

        double epsilon;
        double threshold;
        std::vector<Measurement> measures;
        std::vector<Sensor> sensors;
};


#endif //QUALITAIR_SIMILARDETECTION_H
