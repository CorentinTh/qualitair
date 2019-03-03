//
// Created by Wallyn Valentin on 17/02/2019.
//

#ifndef QUALITAIR_GEOFILTER_H
#define QUALITAIR_GEOFILTER_H


#include "Filter.h"

// TODO: move BBox, it not belong here
typedef struct {
    double left;   // min longitude    [-180, 180[
    double top;    // max latitude     [ -90,  90[
    double right;  // max longitude    [-180, 180[
    double bottom; // min latitude     [ -90,  90[
    // + top > bottom, left < right
} BBox;


class GeoFilter : public Filter {
    public:
            virtual void applyTo(QueryBuilder &qb);

            void setBBox(const BBox &bbox);
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
