//
// Created by Wallyn Valentin on 17/02/2019.
//

#ifndef QUALITAIR_AGGREGATION_H
#define QUALITAIR_AGGREGATION_H


#include <string>
#include "IDataProcess.h"
#include "../../globals.h"

class Aggregation : public IDataProcess {
    public:
        double computeAverage();
        double computeExtrems();
        double computeDeviation();

        json apply() override;

        Aggregation & operator = ( Aggregation other );
        Aggregation ( const Aggregation & other );
        Aggregation ( pointCollection & data, std::string formula);
        virtual ~Aggregation ( );
    
    protected:
        friend void swap(Aggregation & first, Aggregation & second);

        std::string formula;
        pointCollection points;
};


#endif //QUALITAIR_AGGREGATION_H
