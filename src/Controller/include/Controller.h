//
// Created by Wallyn Valentin on 17/02/2019.
//

#ifndef QUALITAIR_CONTROLLER_H
#define QUALITAIR_CONTROLLER_H


#include <vector>
#include "Command.h"

class Controller {
    public:
        Controller & operator = ( Controller other );
        Controller ( const Controller & other );
        Controller ( char ** argv );
        virtual ~Controller ( );
        void execute();

    protected:
        Command* parseCommand();
        friend void swap(Controller & first, Controller & second);

    private:
        static std::vector<std::string> unjoinString(std::string string);
        char ** argv;
};


#endif //QUALITAIR_CONTROLLER_H
