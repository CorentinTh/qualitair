//
// Created by Wallyn Valentin on 17/02/2019.
//

#ifndef QUALITAIR_ETL_H
#define QUALITAIR_ETL_H


#include "IETL.h"

class ETL : public IETL {
public:

    enum {
        MEASURE, ATTRIBUTE, SENSOR
    } data_type;

    static ETL &getInstance() {
        static ETL instance;
        return instance;
    }

    bool ingest(json data) override {
        return false;
    }

    void* getData(json config) override;

    ETL(ETL const &) = default;

    void operator=(ETL const &) = delete;

private:
    ETL() {}
};


#endif //QUALITAIR_ETL_H
