//
// Created by Wallyn Valentin on 17/02/2019.
//

#ifndef QUALITAIR_MEASUREMENT_H
#define QUALITAIR_MEASUREMENT_H


#include "Sensor.h"
#include "Attribute.h"

class Measurement {
    public:
        int getTimestamp() const;
        double getValue() const;
        Sensor getSensor() const;
        Attribute getAttribute() const;

        Measurement & operator = ( Measurement other );
        Measurement ( const Measurement & other );
        Measurement ( int timestamp, Sensor sensor, Attribute attribute, double value );

    bool operator==(const Measurement &rhs) const;

    bool operator!=(const Measurement &rhs) const;

    virtual ~Measurement ( );
        
    protected:
        friend void swap(Measurement & first, Measurement & second);

        int timestamp;
        double value;
        Sensor sensor;
        Attribute attribute;
};


#endif //QUALITAIR_MEASUREMENT_H
