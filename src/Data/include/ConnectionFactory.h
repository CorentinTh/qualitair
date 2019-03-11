//
//        ----[  QUALIT'AIR  ]----
//
//    Marsaud Menseau Thomasset Wallyn
//  Copyright © 2019 - All right reserved
//

#ifndef QUALITAIR_CONNECTIONFACTORY_H
#define QUALITAIR_CONNECTIONFACTORY_H


#include <SQLiteCpp/Database.h>

class ConnectionFactory {
public:
    static SQLite::Database *getConnection();

    static void setDatabase(std::string databasePath);

    static void initializeDatabase();

private:
    static std::string databasePath;
    static SQLite::Database *database;
};


#endif //QUALITAIR_CONNECTIONFACTORY_H
