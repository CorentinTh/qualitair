//
// Created by Wallyn Valentin on 17/02/2019.
//

#ifndef QUALITAIR_ATTRIBUTE_H
#define QUALITAIR_ATTRIBUTE_H


#include <string>

class Attribute {
    public:
        std::string getUnit();
        int getId();
        std::string getDescription();

        Attribute & operator = ( Attribute other );
        Attribute ( const Attribute & other );
        Attribute ( );
        virtual ~Attribute ( );

    protected:
        friend void swap(Attribute & first, Attribute & second);

        std::string unit;
        int attributeId;
        std::string description;
};


#endif //QUALITAIR_ATTRIBUTE_H
