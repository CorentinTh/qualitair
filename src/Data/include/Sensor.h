//
// Created by Wallyn Valentin on 17/02/2019.
//

#ifndef QUALITAIR_SENSOR_H
#define QUALITAIR_SENSOR_H


#include <string>

class Sensor {
    public:
        std::string getId();
        double getLatitude();
        double getLongitude();
        std::string getDescription();

        Sensor & operator = ( Sensor other );
        Sensor ( const Sensor & other );
        Sensor ( std::string sensorId, double latitude, double longitude, std::string description);
        virtual ~Sensor ( );

    protected:
        friend void swap(Sensor & first, Sensor & second);
        
        std::string sensorId;
        double latitude;
        double longitude;
        std::string description;
};


#endif //QUALITAIR_SENSOR_H
