//
// Created by Wallyn Valentin on 17/02/2019.
//

#ifndef QUALITAIR_GEOFILTER_H
#define QUALITAIR_GEOFILTER_H


#include "Filter.h"
#include "../../Data/include/BBox.h"

class GeoFilter : public Filter {
    public:
            virtual void applyTo(QueryBuilder &qb);

            //TODO
            void setBBox(BBox &bbox);
            void extend(double valElargissement);

            GeoFilter & operator = ( GeoFilter other );
            GeoFilter ( const GeoFilter & other );
            GeoFilter ( );
            virtual ~GeoFilter ( );
    
    protected:
            friend void swap(GeoFilter & first, GeoFilter & second);
    
            BBox bbox;
};

#endif //QUALITAIR_GEOFILTER_H
