//
// Created by Wallyn Valentin on 17/02/2019.
//

#ifndef QUALITAIR_IOUTPUT_H
#define QUALITAIR_IOUTPUT_H


#include <string>

class IOutput {
    public:
        virtual ~IOutput() {}
        virtual void printSpikes(std::string dataJson, std::string filename) = 0;
        virtual void printStats(std::string dataJson, std::string filename) = 0;
        virtual void printSim(std::string dataJson, std::string filename) = 0;
        virtual void printBroken(std::string dataJson, std::string filename) = 0;
        virtual void printIngest(std::string dataJson, std::string filename) = 0;
};


#endif //QUALITAIR_IOUTPUT_H
