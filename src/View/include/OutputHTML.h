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
    
        virtual void printSpikes(std::string dataJson);
        virtual void printStats(std::string dataJson);
        virtual void printSim(std::string dataJson);
        virtual void printBroken(std::string dataJson);
        virtual void printIngest(std::string dataJson);
    
        OutputHTML(OutputHTML const&)       = delete;
        void operator=(OutputHTML const&)  = delete;
    
    private:
        OutputHTML();
};


#endif //QUALITAIR_OUTPUTHTML_H
