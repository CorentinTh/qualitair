//
// Created by vwallyn on 03/03/19.
//

#ifndef QUALITAIR_ATMOCOMPUTER_H
#define QUALITAIR_ATMOCOMPUTER_H

#include "IDataProcess.h"
#include "../../globals.h"

class ATMOComputer : public IDataProcess {
    public:
        json * apply() override;

        ATMOComputer & operator = ( ATMOComputer other );
        ATMOComputer ( const ATMOComputer & other );
        ATMOComputer ( pointCollection & data);
        virtual ~ATMOComputer ( );
    
    protected:
        friend void swap(ATMOComputer & first, ATMOComputer & second);
        int computeAtmo() const;
        
        pointCollection points;
};

#endif //QUALITAIR_ATMOCOMPUTER_H
