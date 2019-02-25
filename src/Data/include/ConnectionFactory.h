//
// Created by Wallyn Valentin on 17/02/2019.
//

#ifndef QUALITAIR_CONNECTIONFACTORY_H
#define QUALITAIR_CONNECTIONFACTORY_H


#include <SQLiteCpp/Database.h>

class ConnectionFactory {
    public:
        static SQLite::Database * getConnection();
};


#endif //QUALITAIR_CONNECTIONFACTORY_H
