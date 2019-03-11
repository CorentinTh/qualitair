//
//        ----[  QUALIT'AIR  ]----
//
//    Marsaud Menseau Thomasset Wallyn
//  Copyright © 2019 - All right reserved
//

#include "../include/GeoFilter.h"
#include <stdexcept>

void GeoFilter::applyTo(IData &qb) {
    qb.where("Longitude >= ?").bind(this->bbox.getLeft());
    qb.andWhere("Latitude <= ?").bind(this->bbox.getTop());
    qb.andWhere("Longitude <= ?").bind(this->bbox.getRight());
    qb.andWhere("Latitude >= ?").bind(this->bbox.getBottom());
}

void GeoFilter::extend(double valElargissement) {
    if (valElargissement > 0) {
        if (this->bbox.getTop() + valElargissement >= 90
            || this->bbox.getBottom() - valElargissement <= -90
            || this->bbox.getLeft() - valElargissement <= -180
            || this->bbox.getRight() + valElargissement >= 180) {
            // on sort des coordonnées acceptables
            // normalement on se retrouve "de l'autre coté" mais non géré
            throw std::range_error("Une des coordonnées de la BBox est sortie de son domaine de définiton lors de l'élargissement");
        } else {
            this->bbox.setTop(this->bbox.getTop() + valElargissement);
            this->bbox.setBottom(this->bbox.getBottom() - valElargissement);
            this->bbox.setLeft(this->bbox.getLeft() - valElargissement);
            this->bbox.setRight(this->bbox.getRight() + valElargissement);
        }
    } else {
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
    if (bBox.getTop() >= 90
        || bBox.getBottom() <= -90) {
        throw std::invalid_argument("Latitude invalide ou cas non géré (bbox sur 180ème méridien)");
    }
    if (bBox.getLeft() <= -180
        || bBox.getRight() >= 180) {
        throw std::invalid_argument("Longitude invalide ou cas non géré (bbox sur 180ème méridien)");
    }
    if (bBox.getTop() < bBox.getBottom()
        || bBox.getLeft() > bBox.getRight()) {
        throw std::invalid_argument("Coordonnées incohérentes (left > right ou top < bottom) ou cas non géré (bbox sur 180ème méridien)");
    } else {
        this->bbox.setTop(bBox.getTop());
        this->bbox.setBottom(bBox.getBottom());
        this->bbox.setLeft(bBox.getLeft());
        bbox.setRight(bBox.getRight());
    }

}
