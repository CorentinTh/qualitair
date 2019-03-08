//
// Created by Wallyn Valentin on 17/02/2019.
//

#ifndef QUALITAIR_ATTRIBUTE_H
#define QUALITAIR_ATTRIBUTE_H


#include <string>

class Attribute {
    public:
        std::string getId();
        std::string getUnit();
        std::string getDescription();

        Attribute() {}
        Attribute & operator = ( Attribute other );
        Attribute ( const Attribute & other );
        Attribute ( std::string attributeId, std::string unit, std::string description);
        virtual ~Attribute ( );

    bool operator==(const Attribute &rhs) const;

    bool operator!=(const Attribute &rhs) const;

protected:
        friend void swap(Attribute & first, Attribute & second);

        std::string attributeId;
        std::string unit;
        std::string description;
};


#endif //QUALITAIR_ATTRIBUTE_H
