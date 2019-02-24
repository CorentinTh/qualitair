//
// Created by Wallyn Valentin on 17/02/2019.
//

#ifndef QUALITAIR_INTERPOLATER_H
#define QUALITAIR_INTERPOLATER_H


#include "../../globals.h"
#include "../../Data/include/Measurement.h" // ugly

using namespace std;

class Interpolater {
    public:
        pointCollection interpolate(const vector<Measurement> &measures);

        Interpolater & operator = ( Interpolater other );
        Interpolater ( const Interpolater & other );
        Interpolater ( );
        virtual ~Interpolater ( );
        
    protected:
        friend void swap(Interpolater & first, Interpolater & second);

        int step;
};


#endif //QUALITAIR_INTERPOLATER_H
