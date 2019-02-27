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
        json * apply() override;

        std::unordered_map<std::string, double> computeAverage();
        std::unordered_map<std::string, std::pair<double, double>> computeExtrems();
        std::unordered_map<std::string, double> computeDeviation();
        double computeAtmo();

        Aggregation & operator = ( Aggregation other );
        Aggregation ( const Aggregation & other );
        Aggregation ( pointCollection & data);
        virtual ~Aggregation ( );
    
    protected:
        friend void swap(Aggregation & first, Aggregation & second);

        pointCollection points;


};


#endif //QUALITAIR_AGGREGATION_H
