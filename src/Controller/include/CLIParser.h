//
// Created by Wallyn Valentin on 17/02/2019.
//

#ifndef QUALITAIR_CLIPARSER_H
#define QUALITAIR_CLIPARSER_H


#include <string>
#include "argh.h"

class CLIParser {
    public:
        std::string getArgument(std::string name, std::string defaultValue = "");
        std::string getVerb();

        CLIParser & operator = ( CLIParser other );
        CLIParser ( const CLIParser & other );
        CLIParser ( char* const argv[]);
        virtual ~CLIParser ( );

    protected:
        friend void swap(CLIParser & first, CLIParser & second);
        argh::parser parser;
};


#endif //QUALITAIR_CLIPARSER_H
