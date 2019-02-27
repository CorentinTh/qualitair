//
// Created by Wallyn Valentin on 17/02/2019.
//

#include "../include/Interpolater.h"

pointCollection Interpolater::interpolate(const vector<Measurement> &measures){
    return {{{{{"type", 1}}}}};
}

Interpolater &Interpolater::operator=(Interpolater other) {
    return *this;
}

Interpolater::Interpolater(const Interpolater &other) {

}

Interpolater::Interpolater() {

}

Interpolater::~Interpolater() {

}
