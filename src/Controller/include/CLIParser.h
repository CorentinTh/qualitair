//
//        ----[  QUALIT'AIR  ]----
//
//    Marsaud Menseau Thomasset Wallyn
//  Copyright © 2019 - All right reserved
//

#ifndef QUALITAIR_CLIPARSER_H
#define QUALITAIR_CLIPARSER_H

#include <string>
#include "argh.h"

class CLIParser {
public:
    std::string getArgument(std::string name, std::string defaultValue = "") const;

    std::string getVerb() const;

    std::string getMandatoryArgument(int index = 0) const;

    CLIParser &operator=(CLIParser other);

    CLIParser(const CLIParser &other);

    CLIParser(char *const argv[]);

    virtual ~CLIParser();

protected:
    friend void swap(CLIParser &first, CLIParser &second);

    argh::parser parser;
};


#endif //QUALITAIR_CLIPARSER_H
