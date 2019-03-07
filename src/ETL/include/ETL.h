//
// Created by Wallyn Valentin on 17/02/2019.
//

#ifndef QUALITAIR_ETL_H
#define QUALITAIR_ETL_H


#include "IETL.h"
#include "../../Data/include/QueryBuilder.h"
#include "../include/GeoFilter.h"
#include "../include/TimeFilter.h"
#include "../include/AttributeFilter.h"
#include "../include/SensorFilter.h"
#include "../../Data/include/Measurement.h"

class ETL : public IETL {
public:

    enum {
        MEASURE, ATTRIBUTE, SENSOR
    } data_type;

    static ETL &getInstance() {
        static ETL instance;
        return instance;
    }

    long ingest(std::string path) override {
        return false;
    }

    void* getData(json config) override;

    ETL(ETL const &) = default;

    void operator=(ETL const &) = delete;

private:
    void setFilters(QueryBuilder *qb, json config);

    void *extractData(QueryBuilder *pBuilder, json config);

    ETL() {}

    void setMeasurementConfig(QueryBuilder *qb);
    void setSensorConfig(QueryBuilder *qb);
    void setAttributeConfig(QueryBuilder *qb);
};


#endif //QUALITAIR_ETL_H
