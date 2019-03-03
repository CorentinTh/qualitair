//
// Created by vwallyn on 03/03/19.
//

#ifndef QUALITAIR_EXTREMS_H
#define QUALITAIR_EXTREMS_H


#include "IDataProcess.h"
#include "../../globals.h"

class Extrems : public IDataProcess {
    public:
        json * apply() override;
    
        Extrems & operator = ( Extrems other );
        Extrems ( const Extrems & other );
        Extrems ( pointCollection & data);
        virtual ~Extrems ( );
    
    protected:
        friend void swap(Extrems & first, Extrems & second);
        std::unordered_map<std::string, std::pair<double, double>> computeExtrems() const;
    
        pointCollection points;
};

#endif //QUALITAIR_EXTREMS_H
