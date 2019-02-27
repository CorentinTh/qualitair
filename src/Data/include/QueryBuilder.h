//
// Created by Wallyn Valentin on 17/02/2019.
//

#ifndef QUALITAIR_QUERYBUILDER_H
#define QUALITAIR_QUERYBUILDER_H

#include <vector>
#include "IData.h"

enum ConditionOperator {AND, OR};

class QueryBuilder : public IData {
    public:
        QueryBuilder();
        std::string getQuery();
        QueryBuilder & select(std::string field);
        QueryBuilder & from(std::string table);
        QueryBuilder & where(std::string condition);
        QueryBuilder & andWhere(std::string condition);
        QueryBuilder & orWhere(std::string condition);
        QueryBuilder & join(std::string clause);
        SQLite::Statement * execute();

    private:
        std::vector<std::string> attributes;
        std::vector<std::string> tables;
        std::vector<std::string> joinedTables;
        std::vector<std::pair<ConditionOperator, std::string>> conditions;
};


#endif //QUALITAIR_QUERYBUILDER_H
