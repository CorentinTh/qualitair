//
// Created by Wallyn Valentin on 17/02/2019.
//

#ifndef QUALITAIR_SIMILARDETECTION_H
#define QUALITAIR_SIMILARDETECTION_H


#include "IDataProcess.h"

class SimilarDetection : IDataProcess {
    public:
    
        SimilarDetection & operator = ( SimilarDetection other );
        SimilarDetection ( const SimilarDetection & other );
        SimilarDetection ( );
        virtual ~SimilarDetection ( );
    
    protected:
        friend void swap(SimilarDetection & first, SimilarDetection & second);

        double epsilon;
        double threshold;
};


#endif //QUALITAIR_SIMILARDETECTION_H
