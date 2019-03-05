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

    bool ingest(std::vector<std::string> string, DataType dataType);
    void getData();

    ETL(ETL const &) = default;

    void operator=(ETL const &) = delete;

private:
    ETL() {}
};


#endif //QUALITAIR_ETL_H
