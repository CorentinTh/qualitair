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

    ETL(ETL const &) = default;

    void operator=(ETL const &) = delete;

    enum { MEASURE, ATTRIBUTE, SENSOR } DataType;

protected:
    std::vector<std::string> listCSVFiles(std::string path);

private:
    ETL() = default;
};


#endif //QUALITAIR_ETL_H
