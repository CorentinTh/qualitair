//
//        ----[  QUALIT'AIR  ]----
//
//    Marsaud Menseau Thomasset Wallyn
//  Copyright © 2019 - All right reserved
//

#include "../include/ConnectionFactory.h"

SQLite::Database *ConnectionFactory::database = nullptr;

std::string ConnectionFactory::databasePath = "";

SQLite::Database *ConnectionFactory::getConnection() {
    if (database == nullptr) initializeDatabase();
    return database;
}

void ConnectionFactory::setDatabase(std::string dP) {
    databasePath = dP;
    if (database != nullptr) initializeDatabase();
}

void ConnectionFactory::initializeDatabase() {
    database = new SQLite::Database(databasePath, SQLite::OPEN_READWRITE);
}