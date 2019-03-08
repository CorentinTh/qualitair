//
// Created by Wallyn Valentin on 17/02/2019.
//

#ifndef QUALITAIR_SENSORFILTER_H
#define QUALITAIR_SENSORFILTER_H


#include <vector>
#include "Filter.h"

class SensorFilter : public Filter {
    public:
        void applyTo(QueryBuilder &qb) override;


        void addSensor(std::string sensor);
        void addSensors(std::vector<std::string> vectSensors);

        SensorFilter & operator = ( SensorFilter other );
        SensorFilter ( const SensorFilter & other );
        SensorFilter ( );
        virtual ~SensorFilter ( );
    
    protected:
        friend void swap(SensorFilter & first, SensorFilter & second);
    
        std::vector<std::string> sensors;
};


#endif //QUALITAIR_SENSORFILTER_H
