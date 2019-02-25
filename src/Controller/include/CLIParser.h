//
// Created by Wallyn Valentin on 17/02/2019.
//

#ifndef QUALITAIR_CLIPARSER_H
#define QUALITAIR_CLIPARSER_H


#include <string>
#include <vector>

class CLIParser {
    public:
        std::string getArgument(std::string name);
        std::string getVerb();

        CLIParser & operator = ( CLIParser other );
        CLIParser ( const CLIParser & other );
        CLIParser ( std::vector<std::string> args);
        virtual ~CLIParser ( );

    protected:
        friend void swap(CLIParser & first, CLIParser & second);

        std::vector<std::string> args;
};


#endif //QUALITAIR_CLIPARSER_H
