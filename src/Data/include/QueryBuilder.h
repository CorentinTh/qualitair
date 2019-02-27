//
// Created by Wallyn Valentin on 17/02/2019.
//

#ifndef QUALITAIR_QUERYBUILDER_H
#define QUALITAIR_QUERYBUILDER_H

#include "IData.h"

class QueryBuilder : public IData {
    public:
        QueryBuilder();
        std::string getQuery();
        QueryBuilder & select(std::string field);
        QueryBuilder & from(std::string field);
        QueryBuilder & where(std::string condition);
        QueryBuilder & andWhere(std::string condition);
        QueryBuilder & orWhere(std::string condition);
        QueryBuilder & join(std::string clause);
        SQLite::Statement * execute();
};


#endif //QUALITAIR_QUERYBUILDER_H
