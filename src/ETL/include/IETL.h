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

    virtual void *getData(json config) = 0;
};


#endif //QUALITAIR_IETL_H
