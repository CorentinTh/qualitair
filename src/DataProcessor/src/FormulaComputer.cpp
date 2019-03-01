//
// Created by Wallyn Valentin on 17/02/2019.
//

#include "../include/FormulaComputer.h"
#include "exprtk.hpp"

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

    typedef exprtk::symbol_table<double> symbol_table_d;
    typedef exprtk::expression<double>     expression_d;
    typedef exprtk::parser<double>             parser_d;

    symbol_table_d symbol_table;

    std::unordered_map<std::string, double> sums;

    for (auto i = data.begin(); i != data.end() ; ++i)
    {
        for (auto j = i->begin(); j != i->end() ; ++j)
        {
            for (auto k = j->begin(); k != j->end() ; ++k)
            {
                for (std::unordered_map<std::string, int>::const_iterator it = k->begin();
                     it != k->end(); ++it)
                {
                    sums[it->first] += it->second;
                }
            }
        }
    }

    for (auto it = sums.begin(); it!= sums.end(); ++it) {
        symbol_table.add_variable(it->first, it->second);
    }

    symbol_table.add_constants();

    expression_d expression;
    expression.register_symbol_table(symbol_table);

    parser_d parser;
    parser.compile(formula, expression);

    return std::floor((expression.value()) * 100.0 + 0.5) / 100.0;
}

void swap(FormulaComputer &first, FormulaComputer &second) {
    std::swap(first.formula, second.formula);
}
