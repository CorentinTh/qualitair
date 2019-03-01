//
// Created by Wallyn Valentin on 17/02/2019.
//

#ifndef QUALITAIR_QUERYBUILDER_H
#define QUALITAIR_QUERYBUILDER_H

#include <vector>
#include "IData.h"

enum ConditionOperator {AND, OR};
enum ArgumentType {INT, FLOAT, DOUBLE, LONG, STRING};

struct Argument {
    Argument(int position, ArgumentType type, void * value): position(position), type(type), value(value) {};
    int position;
    ArgumentType type;
    void * value;
};

class QueryBuilder : public IData {

    public:
        QueryBuilder() = default;
        ~ QueryBuilder();
        std::string getQuery();
        QueryBuilder & select(std::string field);
        QueryBuilder & from(std::string table);
        QueryBuilder & where(std::string condition);
        QueryBuilder & andWhere(std::string condition);
        QueryBuilder & orWhere(std::string condition);
        QueryBuilder & join(std::string clause);
        QueryBuilder & bind(int position, int arg);
        QueryBuilder & bind(int position, float arg);
        QueryBuilder & bind(int position, double arg);
        QueryBuilder & bind(int position, long arg);
        QueryBuilder & bind(int position, long long arg);
        QueryBuilder & bind(int position, std::string arg);
        SQLite::Statement * execute();


    private:
        static std::string joinStringVector(std::vector<std::string> vector, std::string separator, std::string replaceValue = "");
        std::vector<std::string> attributes;
        std::vector<std::string> tables;
        std::vector<std::string> joinedTables;
        std::vector<std::pair<ConditionOperator, std::string>> conditions;
        std::vector<Argument> arguments;
};


#endif //QUALITAIR_QUERYBUILDER_H
