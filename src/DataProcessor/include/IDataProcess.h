//
// Created by Wallyn Valentin on 17/02/2019.
//

#ifndef QUALITAIR_IDATAPROCESS_H
#define QUALITAIR_IDATAPROCESS_H

#include "nlohmann/json.hpp"
using json = nlohmann::json;

class IDataProcess {
    public:
        virtual ~IDataProcess() {}

        virtual json apply() = 0;
};


#endif //QUALITAIR_IDATAPROCESS_H
