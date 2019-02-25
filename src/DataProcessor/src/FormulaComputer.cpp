//
// Created by Wallyn Valentin on 17/02/2019.
//

#include "../include/FormulaComputer.h"


FormulaComputer &FormulaComputer::operator=(FormulaComputer other) {
    return *this;
}

FormulaComputer::FormulaComputer(const FormulaComputer &other) {

}


FormulaComputer::FormulaComputer(std::string formulaExpr) : formula(formulaExpr) {

}

FormulaComputer::~FormulaComputer() {

}

double FormulaComputer::compute(pointCollection &data) {
    return 0;
}

void swap(FormulaComputer &first, FormulaComputer &second) {

}
