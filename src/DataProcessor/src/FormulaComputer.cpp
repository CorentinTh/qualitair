//
// Created by Wallyn Valentin on 17/02/2019.
//

#include "../include/FormulaComputer.h"


FormulaComputer &FormulaComputer::operator=(FormulaComputer other) {
    swap(*this, other);
    return *this;
}

FormulaComputer::FormulaComputer(const FormulaComputer &other) {
    formula = other.formula;
}


FormulaComputer::FormulaComputer(std::string formulaExpr) : formula(formulaExpr) {

}

FormulaComputer::~FormulaComputer() {

}

double FormulaComputer::compute(pointCollection &data) {

    /*typedef exprtk::symbol_table<double> symbol_table_d;
    typedef exprtk::expression<double>     expression_d;
    typedef exprtk::parser<double>             parser_d;

    symbol_table_d symbol_table;

    symbol_table.add_variable("x",x);
    symbol_table.add_constants();

    expression_d expression;
    expression.register_symbol_table(symbol_table);

    parser_d parser;
    parser.compile(formula, expression);
    */
    return 0;
}

void swap(FormulaComputer &first, FormulaComputer &second) {
    std::swap(first.formula, second.formula);
}
