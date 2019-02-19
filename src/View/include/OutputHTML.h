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
    
        virtual void printSpikes(std::string dataJson, std::string filename);
        virtual void printStats(std::string dataJson, std::string filename);
        virtual void printSim(std::string dataJsonn, std::string filename);
        virtual void printBroken(std::string dataJsonn, std::string filename);
        virtual void printIngest(std::string dataJsonn, std::string filename);
    
        OutputHTML(OutputHTML const&)       = delete;
        void operator=(OutputHTML const&)  = delete;
    
    private:
        OutputHTML();
};


#endif //QUALITAIR_OUTPUTHTML_H
