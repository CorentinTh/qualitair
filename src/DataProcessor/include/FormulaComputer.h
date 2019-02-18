//
// Created by Wallyn Valentin on 17/02/2019.
//

#ifndef QUALITAIR_FORMULACOMPUTER_H
#define QUALITAIR_FORMULACOMPUTER_H

#include <string>

class FormulaComputer {

    public:
        //TODO params
        double compute();

        FormulaComputer & operator = ( FormulaComputer other );
        FormulaComputer ( const FormulaComputer & other );
        FormulaComputer ( std::string formulaExpr );
        virtual ~FormulaComputer ( );
    
    protected:
        friend void swap(FormulaComputer & first, FormulaComputer & second);

        std::string formula;
};


#endif //QUALITAIR_FORMULACOMPUTER_H
