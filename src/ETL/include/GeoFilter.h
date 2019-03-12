//
//        ----[  QUALIT'AIR  ]----
//
//    Marsaud Menseau Thomasset Wallyn
//  Copyright © 2019 - All right reserved
//

#ifndef QUALITAIR_GEOFILTER_H
#define QUALITAIR_GEOFILTER_H


#include "Filter.h"
#include "../../Data/include/BBox.h"

class GeoFilter : public Filter {
public:
    virtual void applyTo(IData &qb);

    void setBBox(const BBox &bBox);

    void extend(double valElargissement);

    GeoFilter &operator=(GeoFilter other);

    GeoFilter(const GeoFilter &other);

    GeoFilter();

    virtual ~GeoFilter();

protected:
    friend void swap(GeoFilter &first, GeoFilter &second);

    BBox bbox;
};

#endif //QUALITAIR_GEOFILTER_H
