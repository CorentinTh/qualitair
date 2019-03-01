//
// Created by Wallyn Valentin on 17/02/2019.
//

#include "../include/GeoFilter.h"
#include <stdexcept>

void GeoFilter::applyTo(QueryBuilder &qb){
    qb.andWhere("longitude >= ? AND latitude >= ? AND longitude <= ? AND latitude <= ?")
        .bind(1, this->bbox.left)
        .bind(2, this->bbox.bottom)
        .bind(3, this->bbox.right)
        .bind(4, this->bbox.top);
}

void GeoFilter::extend(double valElargissement) {
    if (valElargissement > 0){
        if (this->bbox.top + valElargissement >= 90
            || this->bbox.bottom - valElargissement <= -90
            || this->bbox.left - valElargissement <= -180
            || this->bbox.right + valElargissement >= 180){
            // on sort des coordonnées acceptables
            // normalement on se retrouve "de l'autre coté" mais non géré
            throw std::range_error("Une des coordonnées de la BBox est sortie de son domaine de définiton lors de l'élargissement");
        }
        else{
            this->bbox.top = this->bbox.top + valElargissement;
            this->bbox.bottom = this->bbox.bottom - valElargissement;
            this->bbox.left = this->bbox.left - valElargissement;
            this->bbox.right = this->bbox.right + valElargissement;
        }
    }
    else{
        throw std::invalid_argument("valElargissement doit être strictement positif");
    }
}

GeoFilter &GeoFilter::operator=(GeoFilter other) {
    return *this;
}

GeoFilter::GeoFilter(const GeoFilter &other) {

}

GeoFilter::GeoFilter() {

}

GeoFilter::~GeoFilter() {

}

void GeoFilter::setBBox(const BBox &bBox) {
    if (bBox.top >= 90
        || bBox.bottom <= -90
        || bBox.left <= -180
        || bBox.right >= 180
        || bBox.top <= bBox.bottom
        || bBox.left <= bBox.right){
        // bbox incorrecte
        // ou bbox à cheval sur le 180eme Meridien (non géré)
        throw std::invalid_argument("La bbox en entrée n'est pas définie correctement ou cas non géré (bbox sur 180ème méridien)");
    }
    else{
        this->bbox.top = bBox.top;
        this->bbox.bottom = bBox.bottom;
        this->bbox.left = bBox.left;
        this->bbox.right = bBox.right;
    }

}
