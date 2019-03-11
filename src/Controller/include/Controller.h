//
//        ----[  QUALIT'AIR  ]----
//
//    Marsaud Menseau Thomasset Wallyn
//  Copyright © 2019 - All right reserved
//

#ifndef QUALITAIR_CONTROLLER_H
#define QUALITAIR_CONTROLLER_H

#include <vector>
#include "Command.h"
#include "../include/Config.h"

class Controller {
public:
    Controller &operator=(Controller other);

    Controller(const Controller &other);

    Controller(char **argv);

    virtual ~Controller();

    void execute();

protected:
    Command *parseCommand();

    void printHelp() const;

    friend void swap(Controller &first, Controller &second);

private:
    static std::string userManual;
    char **argv;
    Config config;
};


#endif //QUALITAIR_CONTROLLER_H
