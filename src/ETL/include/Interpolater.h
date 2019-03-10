//
// Created by Wallyn Valentin on 17/02/2019.
//

#ifndef QUALITAIR_INTERPOLATER_H
#define QUALITAIR_INTERPOLATER_H


#include "../../globals.h"
#include "../../Data/include/Measurement.h" // ugly
#include "../include/Octree.h"

#include "nlohmann/json.hpp"
using json = nlohmann::json;

using namespace std;

double euclideanSquared(double x0, double y0, double z0, double x1, double y1, double z1);

class Interpolater {
    public:
        pointCollection* interpolate(const vector<Measurement*> &measures, const json &config);

        Interpolater & operator = ( Interpolater other );
        Interpolater ( const Interpolater & other );
        Interpolater ( );
        virtual ~Interpolater ( );
        
    protected:
        friend void swap(Interpolater & first, Interpolater & second);

        int step;

        double interpolate(double x, double y, double z, vector< OT::point_t *> *neigboors);
};


#endif //QUALITAIR_INTERPOLATER_H
