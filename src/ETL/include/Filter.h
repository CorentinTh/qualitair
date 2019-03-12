//
//        ----[  QUALIT'AIR  ]----
//
//    Marsaud Menseau Thomasset Wallyn
//  Copyright © 2019 - All right reserved
//

#ifndef QUALITAIR_FILTER_H
#define QUALITAIR_FILTER_H

#include "../../Data/include/IData.h"
#include <string>


class Filter {
public:
    virtual void applyTo(IData &qb) = 0;
};


#endif //QUALITAIR_FILTER_H
