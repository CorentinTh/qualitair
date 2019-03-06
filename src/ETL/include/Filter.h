//
// Created by Wallyn Valentin on 17/02/2019.
//

#ifndef QUALITAIR_FILTER_H
#define QUALITAIR_FILTER_H

#include "../../Data/include/QueryBuilder.h"
#include <string>
#include "../../Data/include/QueryBuilder.h"


class Filter {
    public:
        virtual void applyTo(QueryBuilder &qb) = 0;
};


#endif //QUALITAIR_FILTER_H
