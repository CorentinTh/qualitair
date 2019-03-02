//
// Created by Wallyn Valentin on 17/02/2019.
//

#include "../include/QueryBuilder.h"
#include "../include/ConnectionFactory.h"

QueryBuilder::~QueryBuilder() {
    for(Argument argument : arguments) {
        if(argument.type == INT) delete (int *) argument.value;
        else if(argument.type == LONG) delete (long long *) argument.value;
        else if(argument.type == FLOAT) delete (float *) argument.value;
        else if(argument.type == DOUBLE) delete (double *) argument.value;
        else if(argument.type == STRING) delete (std::string *) argument.value;
    }
}

QueryBuilder & QueryBuilder::select(std::string field) {
    attributes.push_back(field);
    return * this;
}

QueryBuilder & QueryBuilder::from(std::string table) {
    tables.push_back(table);
    return * this;
}

QueryBuilder & QueryBuilder::where(std::string condition) {
    andWhere(condition);
    return * this;
}

QueryBuilder & QueryBuilder::andWhere(std::string condition) {
    conditions.push_back(make_pair(AND, condition));
    return * this;
}

QueryBuilder & QueryBuilder::orWhere(std::string condition) {
    conditions.push_back(make_pair(OR, condition));
    return * this;
}

QueryBuilder & QueryBuilder::join(std::string clause) {
    joinedTables.push_back(clause);
    return * this;
}

std::string QueryBuilder::getQuery() {
    std::string query = "SELECT ";

    query += joinStringVector(attributes, ", ", "*");
    query += " FROM ";
    query += joinStringVector(tables, ", ", "unknowTable");

    if(!joinedTables.empty()) {
        query += " CROSS JOIN ";
        query += joinStringVector(joinedTables, ", ");
    }

    if(!conditions.empty()) {
        query += " WHERE ";
        for(std::pair<ConditionOperator, std::string> condition : conditions) {
            if(conditions.at(0) != condition) query += condition.first ? " OR " : " AND ";
            query += condition.second;
        }
    }

    query += ";";

    return query;
}

SQLite::Statement * QueryBuilder::execute() {
    SQLite::Database * database = ConnectionFactory::getConnection();
    SQLite::Statement * statement = new SQLite::Statement(* database, getQuery());

    for(Argument argument : arguments) {
        if(argument.type == INT) statement->bind(argument.position, * (int *) argument.value);
        else if(argument.type == LONG) statement->bind(argument.position, * (long long *) argument.value);
        else if(argument.type == FLOAT) statement->bind(argument.position, * (float *) argument.value);
        else if(argument.type == DOUBLE) statement->bind(argument.position, * (double *) argument.value);
        else if(argument.type == STRING) statement->bind(argument.position, * (std::string *) argument.value);
    }

    return statement;
}

QueryBuilder & QueryBuilder::bind(int position, int arg) {
    arguments.push_back(Argument(position, INT, new int(arg)));
    return * this;
}

QueryBuilder & QueryBuilder::bind(int position, long arg) {
    return bind(position, (long long) arg);
}

QueryBuilder & QueryBuilder::bind(int position, long long arg) {
    arguments.push_back(Argument(position, LONG, new long(arg)));
    return * this;
}

QueryBuilder & QueryBuilder::bind(int position, float arg) {
    arguments.push_back(Argument(position, FLOAT, new float(arg)));
    return * this;
}

QueryBuilder & QueryBuilder::bind(int position, double arg) {
    arguments.push_back(Argument(position, DOUBLE, new double(arg)));
    return * this;
}

QueryBuilder & QueryBuilder::bind(int position, std::string arg) {
    arguments.push_back(Argument(position, STRING, new std::string(arg)));
    return * this;
}

std::string QueryBuilder::joinStringVector(std::vector<std::string> vector, std::string separator, std::string replaceValue) {
    std::string result = "";

    if(!vector.empty()) {
        for(std::string string : vector) {
            result += string + separator;
        }
        result.erase(result.size() - separator.size());
    } else {
        result = replaceValue;
    }

    return result;
}