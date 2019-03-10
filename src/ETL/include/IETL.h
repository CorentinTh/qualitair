//
// Created by Wallyn Valentin on 17/02/2019.
//

#ifndef QUALITAIR_IETL_H
#define QUALITAIR_IETL_H


#include "nlohmann/json.hpp"

using json = nlohmann::json;

#include <string>

class IETL {
    public:
        virtual long ingest(std::string path) = 0;

    /**
     * @param {json}            config
     * @param {ETL::DataType}   config["type"]
     * @param {bool}            config["hasBBox"]
     * @param {bool}            config["hasStart"]
     * @param {bool}            config["hasEnd"]
     * @param {bool}            config["hasSensors"]
     * @param {bool}            config["hasAttributes"]
     * @param {bool}            config["doInterpolation"]
     * @param {double}          config["BBox"]["left"]
     * @param {double}          config["BBox"]["right"]
     * @param {double}          config["BBox"]["top"]
     * @param {double}          config["BBox"]["bottom"]
     * @param {double}          config["start"]
     * @param {double}          config["end"]
     * @param {double}          config["spatialGranularity"]
     * @param {double}          config["temporalGranularity"]
     * @param {double}          config["minimalInterDistance"]["longitude"]
     * @param {double}          config["minimalInterDistance"]["latitude"]
     * @param {double}          config["minimalInterDistance"]["time"]
     * @param {string[]}        config["sensors"]
     * @param {string[]}        config["attributes"]
     * @return
     */
    virtual void *getData(json config, unsigned int recurseCount=0) = 0;
};


#endif //QUALITAIR_IETL_H
