//
// Created by Wallyn Valentin on 17/02/2019.
//

#ifndef QUALITAIR_OUTPUTHTML_H
#define QUALITAIR_OUTPUTHTML_H


#include "IOutput.h"

class OutputHTML : public IOutput {
    public:
        static OutputHTML& getInstance()
        {
            static OutputHTML instance;
            return instance;
        }
    
        virtual void printSpikes();
        virtual void printStats();
        virtual void printSim();
        virtual void printBroken();
        virtual void printIngest();
    
        OutputHTML(OutputHTML const&)       = delete;
        void operator=(OutputHTML const&)  = delete;
    
    private:
        OutputHTML() {}
};


#endif //QUALITAIR_OUTPUTHTML_H
