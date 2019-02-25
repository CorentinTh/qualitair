//
// Created by Wallyn Valentin on 17/02/2019.
//

#include "../include/QueryBuilder.h"

QueryBuilder::QueryBuilder() {

}

std::string QueryBuilder::getQuery() {
    return std::__cxx11::string();
}

QueryBuilder &QueryBuilder::select(std::string field) {
    return *this;
}

QueryBuilder &QueryBuilder::from(std::string field) {
    return *this;
}

QueryBuilder &QueryBuilder::where(std::string condition) {
    return *this;
}

QueryBuilder &QueryBuilder::andWhere(std::string condition) {
    return *this;
}

QueryBuilder &QueryBuilder::orWhere(std::string condition) {
    return *this;
}

QueryBuilder &QueryBuilder::join(std::string clause) {
    return *this;
}

SQLite::Statement *QueryBuilder::execute() {
    return nullptr;
}
