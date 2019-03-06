//
// Created by Wallyn Valentin on 17/02/2019.
//

#include "../include/GeoFilter.h"
#include <stdexcept>

void GeoFilter::applyTo(QueryBuilder &qb){
    qb.where("longitude >= ?").bind(this->bbox.getLeft());
    qb.andWhere("latitude <= ?").bind(this->bbox.getTop());
    qb.andWhere("longitude <= ?").bind(this->bbox.getRight());
    qb.andWhere("latitude >= ?").bind(this->bbox.getBottom());
}

void GeoFilter::extend(double valElargissement) {
    if (valElargissement > 0){
        if (this->bbox.getTop() + valElargissement >= 90
            || this->bbox.getBottom() - valElargissement <= -90
            || this->bbox.getLeft() - valElargissement <= -180
            || this->bbox.getRight() + valElargissement >= 180){
            // on sort des coordonnées acceptables
            // normalement on se retrouve "de l'autre coté" mais non géré
            throw std::range_error("Une des coordonnées de la BBox est sortie de son domaine de définiton lors de l'élargissement");
        }
        else{
            this->bbox.setTop(this->bbox.getTop() + valElargissement);
            this->bbox.setBottom(this->bbox.getBottom() - valElargissement);
            this->bbox.setLeft(this->bbox.getLeft() - valElargissement);
            this->bbox.setRight(this->bbox.getRight() + valElargissement);
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

void GeoFilter::setBBox(BBox &bBox) {
    if (bBox.getTop() >= 90
        || bBox.getBottom() <= -90
        || bBox.getLeft() <= -180
        || bBox.getRight() >= 180
        || bBox.getTop() <= bBox.getBottom()
        || bBox.getLeft() >= bBox.getRight()){
        // bbox incorrecte
        // ou bbox à cheval sur le 180eme Meridien (non géré)
        throw std::invalid_argument("La bbox en entrée n'est pas définie correctement ou cas non géré (bbox sur 180ème méridien)");
    }
    else{
        this->bbox.setTop(bBox.getTop());
        this->bbox.setBottom(bBox.getBottom());
        this->bbox.setLeft(bBox.getLeft());
        this->bbox.setRight(bBox.getRight());
    }

}
