//
//        ----[  QUALIT'AIR  ]----
//
//    Marsaud Menseau Thomasset Wallyn
//  Copyright © 2019 - All right reserved
//

#ifndef QUALITAIR_OUTPUTCLI_H
#define QUALITAIR_OUTPUTCLI_H


#include "IOutput.h"

class OutputCLI : public IOutput {
public:
    static OutputCLI &getInstance() {
        static OutputCLI instance;
        return instance;
    }

    void printSpikes(json data, std::string filename = "");

    virtual void printStats(json data, std::string filename = "");

    virtual void printSim(json data, std::string filename = "");

    virtual void printBroken(json data, std::string filename = "");

    virtual void printIngest(json data, std::string filename = "");

    virtual void printSensors(json data, std::string filename = "");

    OutputCLI(OutputCLI const &) = delete;

    void operator=(OutputCLI const &) = delete;

private:
    OutputCLI();
};


#endif //QUALITAIR_OUTPUTCLI_H
