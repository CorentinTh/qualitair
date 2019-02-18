//
// Created by Wallyn Valentin on 17/02/2019.
//

#ifndef QUALITAIR_IDATA_H
#define QUALITAIR_IDATA_H

#include <string>

class IData {
    public:
        virtual ~IData() {}
        virtual void select(std::string field) = 0;
        virtual void from(std::string field) = 0;
        virtual void where(std::string condition) = 0;
        virtual void andWhere(std::string condition) = 0;
        virtual void orWhere(std::string condition) = 0;
        virtual void join(std::string clause) = 0;
        //TODO return type
        virtual void execute() = 0;
};


#endif //QUALITAIR_IDATA_H
