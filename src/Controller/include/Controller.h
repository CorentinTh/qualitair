//
// Created by Wallyn Valentin on 17/02/2019.
//

#ifndef QUALITAIR_CONTROLLER_H
#define QUALITAIR_CONTROLLER_H


#include "Command.h"

class Controller {
    public:

        Controller & operator = ( Controller other );
        Controller ( const Controller & other );
        Controller ( );
        virtual ~Controller ( );

    protected:
        Command* parseCommand();
        friend void swap(Controller & first, Controller & second);
};


#endif //QUALITAIR_CONTROLLER_H
