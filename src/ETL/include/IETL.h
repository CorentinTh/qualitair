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
        virtual bool ingest(json data) = 0;
        // TODO this is not void + add param
        virtual void getData() = 0;
};


#endif //QUALITAIR_IETL_H
