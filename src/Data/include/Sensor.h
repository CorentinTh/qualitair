//
// Created by Wallyn Valentin on 17/02/2019.
//

#ifndef QUALITAIR_SENSOR_H
#define QUALITAIR_SENSOR_H


#include <string>
#include "nlohmann/json.hpp"
using json = nlohmann::json;

class Sensor {
    public:
        std::string getId();
        double getLatitude();
        double getLongitude();
        std::string getDescription();

        Sensor() {}
        Sensor & operator = ( Sensor other );
        bool operator==(const Sensor &rhs) const;
        Sensor ( const Sensor & other );
        Sensor ( std::string sensorId, double latitude, double longitude, std::string description);
        virtual ~Sensor ( );

    protected:
        friend void swap(Sensor & first, Sensor & second);
        friend void to_json(json& j, const Sensor& s);
        friend void from_json(const json& j, Sensor& s);

        std::string sensorId;
        double latitude;
        double longitude;
        std::string description;
};


#endif //QUALITAIR_SENSOR_H
