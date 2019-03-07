//
// Created by Wallyn Valentin on 17/02/2019.
//

#ifndef QUALITAIR_ETL_H
#define QUALITAIR_ETL_H


#include "IETL.h"

class ETL : public IETL {
public:
    static ETL &getInstance() {
        static ETL instance;
        return instance;
    }

    long ingest(std::string path) override;
    void getData() override;
    int extractDataTypeFromFile(std::string path);

    ETL(ETL const &) = default;

    void operator=(ETL const &) = delete;

    enum { MEASURE, ATTRIBUTE, SENSOR } DataType;

protected:
    static const int NB_ROW_PER_BATCH = 1000;
    std::vector<std::string> listCSVFiles(std::string path);

private:
    ETL() = default;
};


#endif //QUALITAIR_ETL_H
