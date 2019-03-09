//
// Created by Wallyn Valentin on 17/02/2019.
//

#include "../include/ConnectionFactory.h"

SQLite::Database * ConnectionFactory::database = nullptr;
std::string ConnectionFactory::databasePath = "";

SQLite::Database * ConnectionFactory::getConnection() {
    if(database == nullptr) initializeDatabase();
    return database;
}

void ConnectionFactory::setDatabase(std::string dP) {
    databasePath = dP;
    if(database != nullptr) initializeDatabase();
}

void ConnectionFactory::initializeDatabase() {
    database = new SQLite::Database(databasePath, SQLite::OPEN_READWRITE);
}