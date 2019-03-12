//
//        ----[  QUALIT'AIR  ]----
//
//    Marsaud Menseau Thomasset Wallyn
//  Copyright © 2019 - All right reserved
//

#ifndef QUALITAIR_MEASUREMENT_H
#define QUALITAIR_MEASUREMENT_H


#include "Sensor.h"
#include "Attribute.h"

class Measurement {
public:
    long getTimestamp() const;

    double getValue() const;

    Sensor getSensor() const;

    Attribute getAttribute() const;

    Measurement &operator=(Measurement other);

    Measurement(const Measurement &other);

    Measurement(long timestamp, Sensor sensor, Attribute attribute, double value);

    bool operator==(const Measurement &rhs) const;

    bool operator!=(const Measurement &rhs) const;

    virtual ~Measurement();

protected:
    friend void swap(Measurement &first, Measurement &second);

    friend void to_json(json &j, const Measurement &s);

    friend void from_json(const json &j, Measurement &s);

    long timestamp;
    double value;
    Sensor sensor;
    Attribute attribute;
};


#endif //QUALITAIR_MEASUREMENT_H
