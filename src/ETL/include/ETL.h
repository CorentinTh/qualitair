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

    static enum {
        MEASURE, ATTRIBUTE, SENSOR
    } DataType;

    static IETL &getInstance() {
        static ETL instance;
        return instance;
    }

    long ingest(std::string path) override;

    void *getData(json config);

    int extractDataTypeFromFile(std::string path);

    ETL(ETL const &) = default;

    void operator=(ETL const &) = delete;

protected:
    static const int NB_ROW_PER_BATCH = 200;
    std::vector<std::string> listCSVFiles(std::string path);


private:
    void setFilters(QueryBuilder *qb, json config);

    void *extractData(QueryBuilder *pBuilder, json config);

    void setMeasurementConfig(QueryBuilder *qb);
    void setSensorConfig(QueryBuilder *qb);
    void setAttributeConfig(QueryBuilder *qb);
    void createDatabaseIndexs();
    void dropDatabaseIndexs();

    ETL() = default;
};


#endif //QUALITAIR_ETL_H
