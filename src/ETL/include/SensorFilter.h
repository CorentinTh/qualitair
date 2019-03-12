//
//        ----[  QUALIT'AIR  ]----
//
//    Marsaud Menseau Thomasset Wallyn
//  Copyright © 2019 - All right reserved
//

#ifndef QUALITAIR_SENSORFILTER_H
#define QUALITAIR_SENSORFILTER_H


#include <vector>
#include "Filter.h"

class SensorFilter : public Filter {
public:
    void applyTo(IData &qb) override;


    void addSensor(std::string sensor);

    void addSensors(std::vector<std::string> vectSensors);

    SensorFilter &operator=(SensorFilter other);

    SensorFilter(const SensorFilter &other);

    SensorFilter();

    virtual ~SensorFilter();

protected:
    friend void swap(SensorFilter &first, SensorFilter &second);

    std::vector<std::string> sensors;
};


#endif //QUALITAIR_SENSORFILTER_H
