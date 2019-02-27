//
// Created by Wallyn Valentin on 17/02/2019.
//

#include "../include/ConnectionFactory.h"

SQLite::Database * ConnectionFactory::getConnection() {
    if(database == nullptr) database = new SQLite::Database(databasePath);
    return database;
}

void ConnectionFactory::setDatabase(std::string databasePath) {
    ConnectionFactory::databasePath = databasePath;
}
