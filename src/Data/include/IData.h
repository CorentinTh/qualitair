//
//        ----[  QUALIT'AIR  ]----
//
//    Marsaud Menseau Thomasset Wallyn
//  Copyright © 2019 - All right reserved
//

#ifndef QUALITAIR_IDATA_H
#define QUALITAIR_IDATA_H

#include <string>
#include <SQLiteCpp/Statement.h>
#include <vector>

class IData {
public:
    virtual ~IData() {}

    virtual IData &select(std::string field) = 0;

    virtual IData &insert(std::string table) = 0;

    virtual IData &values(std::vector<std::string> attributes) = 0;

    virtual IData &from(std::string table) = 0;

    virtual IData &where(std::string condition) = 0;

    virtual IData &andWhere(std::string condition) = 0;

    virtual IData &orWhere(std::string condition) = 0;

    virtual IData &bind(int arg) = 0;

    virtual IData &bind(double arg) = 0;

    virtual IData &bind(float arg) = 0;

    virtual IData &bind(long arg) = 0;

    virtual IData &bind(long long arg) = 0;

    virtual IData &bind(std::string arg) = 0;

    virtual IData &join(std::string clause) = 0;

    virtual SQLite::Statement *execute() = 0;

    virtual int executeUpdate() = 0;
};


#endif //QUALITAIR_IDATA_H
