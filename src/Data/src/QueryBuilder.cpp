//
// Created by Wallyn Valentin on 17/02/2019.
//

#include "../include/QueryBuilder.h"
#include "../include/ConnectionFactory.h"

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

//TODO: user Corentin's join method when merged
std::string QueryBuilder::getQuery() {
    std::string query = "SELECT ";

    if(this->attributes.size() > 0) {
        for(std::string attribute : this->attributes) {
            query += attribute + ", ";
        }
        query.erase(query.size() - 2);
    } else {
        query += "*";
    }

    query += " FROM ";
    if(this->tables.size() > 0) {
        for(std::string table : this->tables) {
            query += table + ", ";
            query.erase(query.size() - 2);
        }
    } else {
        query += "unknowTable";
    }

    if(this->joinedTables.size() > 0) {
        query += " CROSS JOIN ";
        for(std::string table : this->joinedTables) {
            query += table + ", ";
            query.erase(query.size() - 2);
        }
    }

    if(this->conditions.size() > 0) {
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
    return new SQLite::Statement(* database, this->getQuery());
}