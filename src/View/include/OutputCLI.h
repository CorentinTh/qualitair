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

        virtual void printSpikes(std::string dataJson, std::string filename="");
        virtual void printStats(std::string dataJson, std::string filename="");
        virtual void printSim(std::string dataJson, std::string filename="");
        virtual void printBroken(std::string dataJson, std::string filename="");
        virtual void printIngest(std::string dataJson, std::string filename="");

        OutputCLI(OutputCLI const&)       = delete;
        void operator=(OutputCLI const&)  = delete;

    private:
        OutputCLI();
};


#endif //QUALITAIR_OUTPUTCLI_H
