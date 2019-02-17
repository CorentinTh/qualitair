//
// Created by Wallyn Valentin on 17/02/2019.
//

#ifndef QUALITAIR_MEASUREMENT_H
#define QUALITAIR_MEASUREMENT_H


class Measurement {
    public:
        int getTimestamp();
        double getValue();

        Measurement & operator = ( Measurement other );
        Measurement ( const Measurement & other );
        Measurement ( );
        virtual ~Measurement ( );
        
    protected:
        friend void swap(Measurement & first, Measurement & second);

        int timestamp;
        double value;
};


#endif //QUALITAIR_MEASUREMENT_H
