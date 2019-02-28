//
// Created by Wallyn Valentin on 17/02/2019.
//

#ifndef QUALITAIR_MEASUREMENT_H
#define QUALITAIR_MEASUREMENT_H


class Measurement {
public:
    int getTimestamp() const;

    double getValue() const;

    int getSensorId() const;

    int getAttributeId() const;

    Measurement &operator=(Measurement other);

    Measurement(const Measurement &other);

    Measurement(int timestamp, int sensorId, int attributeId, double value);

    virtual ~Measurement();

protected:
    friend void swap(Measurement &first, Measurement &second);

    int timestamp;
    double value;
    int sensorId;
    int attributeId;
};


#endif //QUALITAIR_MEASUREMENT_H
