//
// Created by Wallyn Valentin on 17/02/2019.
//

#ifndef QUALITAIR_GEOFILTER_H
#define QUALITAIR_GEOFILTER_H


#include "Filter.h"

// TODO: move BBox, it not belong here
typedef struct {
    int left;   // min longitude    [-180, 180[
    int top;    // min latitude     [ -90,  90[
    int right;  // max longitude    [-180, 180[
    int bottom; // max latitude     [ -90,  90[
} BBox;


class GeoFilter : public Filter {
    public:
            virtual std::string apply();

            //TODO
            void setBBox(const BBox &bbox);
            void extend(double ratio);

            GeoFilter & operator = ( GeoFilter other );
            GeoFilter ( const GeoFilter & other );
            GeoFilter ( );
            virtual ~GeoFilter ( );
    
    protected:
            friend void swap(GeoFilter & first, GeoFilter & second);
    
            BBox bbox;
};

#endif //QUALITAIR_GEOFILTER_H
