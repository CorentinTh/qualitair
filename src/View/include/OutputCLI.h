//
// Created by Wallyn Valentin on 17/02/2019.
//

#ifndef QUALITAIR_OUTPUTCLI_H
#define QUALITAIR_OUTPUTCLI_H


#include "IOutput.h"

class OutputCLI : public IOutput {
    public:
        static OutputCLI& getInstance()
        {
            static OutputCLI instance;
            return instance;
        }

        virtual void printSpikes();
        virtual void printStats();
        virtual void printSim();
        virtual void printBroken();
        virtual void printIngest();

        OutputCLI(OutputCLI const&)       = delete;
        void operator=(OutputCLI const&)  = delete;

    private:
        OutputCLI() {}
};


#endif //QUALITAIR_OUTPUTCLI_H
