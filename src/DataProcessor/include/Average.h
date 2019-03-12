//
//        ----[  QUALIT'AIR  ]----
//
//    Marsaud Menseau Thomasset Wallyn
//  Copyright © 2019 - All right reserved
//

#ifndef QUALITAIR_MEAN_H
#define QUALITAIR_MEAN_H

#include "IDataProcess.h"
#include "../../globals.h"

class Average : public IDataProcess {
public:
    json *apply() override;

    Average &operator=(Average other);

    Average(const Average &other);

    Average(pointCollection &data);

    virtual ~Average();

protected:
    friend void swap(Average &first, Average &second);

    std::unordered_map<std::string, double> computeAverage() const;

    pointCollection points;
};

#endif //QUALITAIR_MEAN_H
