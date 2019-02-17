//
// Created by Wallyn Valentin on 17/02/2019.
//

#ifndef QUALITAIR_AGGREGATION_H
#define QUALITAIR_AGGREGATION_H


#include <string>
#include "IDataProcess.h"

class Aggregation : public IDataProcess {
    public:
        //TODO params
        double computeAverage();
        double computeExtrems();
        double computeDeviation();
        
        Aggregation & operator = ( Aggregation other );
        Aggregation ( const Aggregation & other );
        Aggregation ( );
        virtual ~Aggregation ( );
    
    protected:
        friend void swap(Aggregation & first, Aggregation & second);

        std::string formula;
};


#endif //QUALITAIR_AGGREGATION_H
