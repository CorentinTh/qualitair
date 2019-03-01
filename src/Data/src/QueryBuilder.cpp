//
// Created by Wallyn Valentin on 17/02/2019.
//

#include "../include/QueryBuilder.h"
#include "../include/ConnectionFactory.h"

QueryBuilder::~QueryBuilder() {
    for(Argument argument : this->arguments) {
        if(argument.type == INT) delete (int *) argument.value;
        else if(argument.type == LONG) delete (long long *) argument.value;
        else if(argument.type == FLOAT) delete (float *) argument.value;
        else if(argument.type == DOUBLE) delete (double *) argument.value;
        else if(argument.type == STRING) delete (std::string *) argument.value;
    }
}

QueryBuilder & QueryBuilder::select(std::string field) {
    this->attributes.push_back(field);
    return * this;
}

QueryBuilder & QueryBuilder::from(std::string table) {
    this->tables.push_back(table);
    return * this;
}

QueryBuilder & QueryBuilder::where(std::string condition) {
    this->andWhere(condition);
    return * this;
}

QueryBuilder & QueryBuilder::andWhere(std::string condition) {
    this->conditions.push_back(make_pair(AND, condition));
    return * this;
}

QueryBuilder & QueryBuilder::orWhere(std::string condition) {
    this->conditions.push_back(make_pair(OR, condition));
    return * this;
}

QueryBuilder & QueryBuilder::join(std::string clause) {
    this->joinedTables.push_back(clause);
    return * this;
}

std::string QueryBuilder::getQuery() {
    std::string query = "SELECT ";

    query += joinStringVector(this->attributes, ", ", "*");
    query += " FROM ";
    query += joinStringVector(this->tables, ", ", "unknowTable");

    if(!this->joinedTables.empty()) {
        query += " CROSS JOIN ";
        query += joinStringVector(this->joinedTables, ", ");
    }

    if(!this->conditions.empty()) {
        query += " WHERE ";
        for(std::pair<ConditionOperator, std::string> condition : this->conditions) {
            if(this->conditions.at(0) != condition) query += condition.first ? " OR " : " AND ";
            query += condition.second;
        }
    }

    query += ";";

    return query;
}

SQLite::Statement * QueryBuilder::execute() {
    SQLite::Database * database = ConnectionFactory::getConnection();
    SQLite::Statement * statement = new SQLite::Statement(* database, this->getQuery());

    for(Argument argument : this->arguments) {
        if(argument.type == INT) statement->bind(argument.position, * (int *) argument.value);
        else if(argument.type == LONG) statement->bind(argument.position, * (long long *) argument.value);
        else if(argument.type == FLOAT) statement->bind(argument.position, * (float *) argument.value);
        else if(argument.type == DOUBLE) statement->bind(argument.position, * (double *) argument.value);
        else if(argument.type == STRING) statement->bind(argument.position, * (std::string *) argument.value);
    }

    return statement;
}

QueryBuilder & QueryBuilder::bind(int position, int arg) {
    this->arguments.push_back(Argument(position, INT, new int(arg)));
    return * this;
}

QueryBuilder & QueryBuilder::bind(int position, long arg) {
    return this->bind(position, (long long) arg);
}

QueryBuilder & QueryBuilder::bind(int position, long long arg) {
    this->arguments.push_back(Argument(position, LONG, new long(arg)));
    return * this;
}

QueryBuilder & QueryBuilder::bind(int position, float arg) {
    this->arguments.push_back(Argument(position, FLOAT, new float(arg)));
    return * this;
}

QueryBuilder & QueryBuilder::bind(int position, double arg) {
    this->arguments.push_back(Argument(position, DOUBLE, new double(arg)));
    return * this;
}

QueryBuilder & QueryBuilder::bind(int position, std::string arg) {
    this->arguments.push_back(Argument(position, STRING, new std::string(arg)));
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