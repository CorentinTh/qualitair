//
//        ----[  QUALIT'AIR  ]----
//
//    Marsaud Menseau Thomasset Wallyn
//  Copyright © 2019 - All right reserved
//

#ifndef QUALITAIR_ATTRIBUTEFILTER_H
#define QUALITAIR_ATTRIBUTEFILTER_H


#include <vector>
#include "Filter.h"

class AttributeFilter : public Filter {
public:
    void applyTo(IData &qb) override;

    void addAttribute(std::string attribute);

    void addAttributes(std::vector<std::string> vectAttributes);

    AttributeFilter &operator=(AttributeFilter other);

    AttributeFilter(const AttributeFilter &other);

    AttributeFilter();

    virtual ~AttributeFilter();

protected:
    friend void swap(AttributeFilter &first, AttributeFilter &second);

    std::vector<std::string> attributes;
};


#endif //QUALITAIR_ATTRIBUTEFILTER_H
