//
// Created by Wallyn Valentin on 17/02/2019.
//

#ifndef QUALITAIR_CONTROLLER_H
#define QUALITAIR_CONTROLLER_H


#include <vector>
#include "Command.h"
#include "../include/Config.h"

class Controller {
    public:
        Controller & operator = ( Controller other );
        Controller ( const Controller & other );
        Controller ( char ** argv );
        virtual ~Controller ( );
        void execute();

    protected:
        Command* parseCommand();
        void printHelp() const;
        friend void swap(Controller & first, Controller & second);

    private:
        static time_t parseRFC3339Date(std::string stringDate);
        static std::vector<std::string> unjoinString(std::string string);
        static std::string userManual;
        char ** argv;
        Config config;
};


#endif //QUALITAIR_CONTROLLER_H
