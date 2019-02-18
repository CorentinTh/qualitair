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
        void select(std::string field);
        void from(std::string field);
        void where(std::string condition);
        void andWhere(std::string condition);
        void orWhere(std::string condition);
        void join(std::string clause);
        void execute();
};


#endif //QUALITAIR_QUERYBUILDER_H
