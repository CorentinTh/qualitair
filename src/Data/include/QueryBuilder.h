//
//        ----[  QUALIT'AIR  ]----
//
//    Marsaud Menseau Thomasset Wallyn
//  Copyright © 2019 - All right reserved
//

#ifndef QUALITAIR_QUERYBUILDER_H
#define QUALITAIR_QUERYBUILDER_H

#include <vector>
#include "IData.h"

enum ConditionOperator {
    AND, OR
};
enum ArgumentType {
    INT, FLOAT, DOUBLE, LONG, STRING
};
enum RequestType {
    SELECT, INSERT
};

struct Argument {
    Argument(int position, ArgumentType type, void *value) : position(position), type(type), value(value) {};
    int position;
    ArgumentType type;
    void *value;
};

//TODO use IDataInterface instead of using QueryBuilder (implementation) in the code !
class QueryBuilder : public IData {

public:
    QueryBuilder() : argumentIndex(0), requestType(SELECT) {};

    ~ QueryBuilder();

    std::string getQuery();

    QueryBuilder &select(std::string field);

    QueryBuilder &insert(std::string table);

    QueryBuilder &values(std::vector<std::string> attributes);

    QueryBuilder &from(std::string table);

    QueryBuilder &where(std::string condition);

    QueryBuilder &andWhere(std::string condition);

    QueryBuilder &orWhere(std::string condition);

    QueryBuilder &join(std::string clause);

    QueryBuilder &bind(int arg);

    QueryBuilder &bind(float arg);

    QueryBuilder &bind(double arg);

    QueryBuilder &bind(long arg);

    QueryBuilder &bind(long long arg);

    QueryBuilder &bind(std::string arg);

    QueryBuilder &orderBy(std::string attribute);

    SQLite::Statement *execute();

    int executeUpdate();

private:
    static std::string joinStringVector(std::vector<std::string> vector, std::string separator, std::string replaceValue = "");

    int argumentIndex;
    RequestType requestType;
    std::vector<std::string> attributes;
    std::vector<std::string> tables;
    std::vector<std::string> joinedTables;
    std::vector<std::pair<ConditionOperator, std::string>> conditions;
    std::vector<Argument> arguments;
    std::string orderByAttribute;
};


#endif //QUALITAIR_QUERYBUILDER_H
