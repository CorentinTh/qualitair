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
        enum DataType {MEASURE, ATTRIBUTE, SENSOR};
        virtual bool ingest(std::vector<std::string> data, DataType dataType) = 0;
        virtual void getData() = 0;
};


#endif //QUALITAIR_IETL_H
