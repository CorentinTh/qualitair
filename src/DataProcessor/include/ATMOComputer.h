//
//        ----[  QUALIT'AIR  ]----
//
//    Marsaud Menseau Thomasset Wallyn
//  Copyright © 2019 - All right reserved
//

#ifndef QUALITAIR_ATMOCOMPUTER_H
#define QUALITAIR_ATMOCOMPUTER_H

#include "IDataProcess.h"
#include "../../globals.h"

class ATMOComputer : public IDataProcess {
public:
    json *apply() override;

    ATMOComputer &operator=(ATMOComputer other);

    ATMOComputer(const ATMOComputer &other);

    ATMOComputer(pointCollection &data);

    virtual ~ATMOComputer();

protected:
    friend void swap(ATMOComputer &first, ATMOComputer &second);

    int computeAtmo() const;

    double getAveragePM10() const;

    std::unordered_map<std::string, double> getAverageMaxima() const;

    pointCollection points;
};

#endif //QUALITAIR_ATMOCOMPUTER_H
