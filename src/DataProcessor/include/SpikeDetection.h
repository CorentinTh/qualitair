//
// Created by Wallyn Valentin on 17/02/2019.
//

#ifndef QUALITAIR_SPIKEDETECTION_H
#define QUALITAIR_SPIKEDETECTION_H


#include "IDataProcess.h"
#include "../../globals.h"

class SpikeDetection : public IDataProcess {
    public:
        SpikeDetection & operator = ( SpikeDetection other );

        json apply() override;

        SpikeDetection ( const SpikeDetection & other );
        SpikeDetection ( pointCollection & data, std::string formula );
        virtual ~SpikeDetection ( );
    
    protected:
        friend void swap(SpikeDetection & first, SpikeDetection & second);

        double valueThreshold;
        double areaThreshold;
        int delay;
        pointCollection points;
        std::string formula;
};


#endif //QUALITAIR_SPIKEDETECTION_H
