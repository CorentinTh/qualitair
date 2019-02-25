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
    
        virtual void printSpikes(json dataJson, std::string filename);
        virtual void printStats(json dataJson, std::string filename);
        virtual void printSim(json dataJsonn, std::string filename);
        virtual void printBroken(json dataJsonn, std::string filename);
        virtual void printIngest(json dataJsonn, std::string filename);
    
        OutputHTML(OutputHTML const&)       = delete;
        void operator=(OutputHTML const&)  = delete;
    
    private:
        OutputHTML();
};


#endif //QUALITAIR_OUTPUTHTML_H
