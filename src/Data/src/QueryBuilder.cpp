//
// Created by Wallyn Valentin on 17/02/2019.
//

#include <SQLiteCpp/Transaction.h>
#include <iostream>
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
    requestType = SELECT;
    attributes.push_back(field);
    return * this;
}

QueryBuilder & QueryBuilder::insert(std::string table) {
    requestType = INSERT;
    tables.push_back(table);
    return * this;
}

QueryBuilder & QueryBuilder::values(std::vector<std::string> attributes) {
    this->attributes = attributes;
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
    std::string query;

    if(requestType == SELECT) {
        query += "SELECT ";
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
    } else {
        query += "INSERT INTO ";
        query += tables[0];
        query += "(" + joinStringVector(attributes, ", ") + ")";
        query += " VALUES ";
        query += "(";

        for(int j = 0; j < attributes.size(); j++) query += "?, ";
        query = query.substr(0, query.size() - 2);

        query += ")";
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

int QueryBuilder::executeUpdate() {
    int nbRows = 0;
    SQLite::Database * database = ConnectionFactory::getConnection();
    SQLite::Transaction transaction(* database);

    for(int i = 0; i < arguments.size(); i += attributes.size()) {
        SQLite::Statement * statement = new SQLite::Statement(* database, getQuery());
        for(int j = 0; j < attributes.size(); j++) {
            if(arguments[i + j].type == INT) statement->bind(j + 1, * (int *) arguments[i + j].value);
            else if(arguments[i + j].type == LONG) statement->bind(j + 1, * (long long *) arguments[i + j].value);
            else if(arguments[i + j].type == FLOAT) statement->bind(j + 1, * (float *) arguments[i + j].value);
            else if(arguments[i + j].type == DOUBLE) statement->bind(j + 1, * (double *) arguments[i + j].value);
            else if(arguments[i + j].type == STRING) statement->bind(j + 1, * (std::string *) arguments[i + j].value);
        }
        std::cout << statement->getQuery() << std::endl;
        nbRows += statement->exec();
        std::cout << nbRows << std::endl;
    }

    transaction.commit();
    return nbRows;
}

QueryBuilder & QueryBuilder::bind(int arg) {
    arguments.push_back(Argument(++argumentIndex, INT, new int(arg)));
    return * this;
}

QueryBuilder & QueryBuilder::bind(long arg) {
    return bind((long long) arg);
}

QueryBuilder & QueryBuilder::bind(long long arg) {
    arguments.push_back(Argument(++argumentIndex, LONG, new long(arg)));
    return * this;
}

QueryBuilder & QueryBuilder::bind(float arg) {
    arguments.push_back(Argument(++argumentIndex, FLOAT, new float(arg)));
    return * this;
}

QueryBuilder & QueryBuilder::bind(double arg) {
    arguments.push_back(Argument(++argumentIndex, DOUBLE, new double(arg)));
    return * this;
}

QueryBuilder & QueryBuilder::bind(std::string arg) {
    arguments.push_back(Argument(++argumentIndex, STRING, new std::string(arg)));
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