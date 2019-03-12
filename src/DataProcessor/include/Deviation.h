//
//        ----[  QUALIT'AIR  ]----
//
//    Marsaud Menseau Thomasset Wallyn
//  Copyright © 2019 - All right reserved
//

#ifndef QUALITAIR_DEVIATION_H
#define QUALITAIR_DEVIATION_H

#include "IDataProcess.h"
#include "../../globals.h"

class Deviation : public IDataProcess {
public:
    json *apply() override;

    Deviation &operator=(Deviation other);

    Deviation(const Deviation &other);

    Deviation(pointCollection &data);

    virtual ~Deviation();

protected:
    friend void swap(Deviation &first, Deviation &second);

    std::unordered_map<std::string, double> computeDeviation() const;

    pointCollection points;
};

#endif //QUALITAIR_DEVIATION_H
