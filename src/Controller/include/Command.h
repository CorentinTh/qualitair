//
// Created by Wallyn Valentin on 17/02/2019.
//

#ifndef QUALITAIR_COMMAND_H
#define QUALITAIR_COMMAND_H


#include <string>
#include "nlohmann/json.hpp"
using json = nlohmann::json;

enum OutputFormat { HUMAN, JSON, HTML };

class Command {
    public:
        virtual void execute() = 0;
        virtual void output() = 0;
    protected:
        std::string database;
};


#endif //QUALITAIR_COMMAND_H
