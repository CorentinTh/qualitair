//
// Created by Wallyn Valentin on 17/02/2019.
//

#ifndef QUALITAIR_INTERPOLATER_H
#define QUALITAIR_INTERPOLATER_H


class Interpolater {
    public:
        // TODO param & return type
        void interpolate();

        Interpolater & operator = ( Interpolater other );
        Interpolater ( const Interpolater & other );
        Interpolater ( );
        virtual ~Interpolater ( );
        
    protected:
        friend void swap(Interpolater & first, Interpolater & second);

        int step;
};


#endif //QUALITAIR_INTERPOLATER_H
