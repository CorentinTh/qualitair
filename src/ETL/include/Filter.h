//
// Created by Wallyn Valentin on 17/02/2019.
//

#ifndef QUALITAIR_FILTER_H
#define QUALITAIR_FILTER_H


#include <string>

class Filter {
    public:
        virtual std::string apply() = 0;
};


#endif //QUALITAIR_FILTER_H
