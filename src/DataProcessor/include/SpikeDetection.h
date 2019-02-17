//
// Created by Wallyn Valentin on 17/02/2019.
//

#ifndef QUALITAIR_SPIKEDETECTION_H
#define QUALITAIR_SPIKEDETECTION_H


#include "IDataProcess.h"

class SpikeDetection : public IDataProcess {
    public:
        SpikeDetection & operator = ( SpikeDetection other );

        void apply() override;

        SpikeDetection ( const SpikeDetection & other );
        SpikeDetection ( );
        virtual ~SpikeDetection ( );
    
    protected:
        friend void swap(SpikeDetection & first, SpikeDetection & second);

        double valueThreshold;
        double areaThreshold;
        int delay;
};


#endif //QUALITAIR_SPIKEDETECTION_H
