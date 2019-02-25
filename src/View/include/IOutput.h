//
// Created by Wallyn Valentin on 17/02/2019.
//

#ifndef QUALITAIR_IOUTPUT_H
#define QUALITAIR_IOUTPUT_H

#include <nlohmann/json.hpp>
#include <string>
// for convenience
using json = nlohmann::json;


class IOutput {
    public:
        virtual ~IOutput() {}
        virtual void printSpikes(json dataJson, std::string filename) = 0;
        virtual void printStats(json dataJson, std::string filename) = 0;
        virtual void printSim(json dataJson, std::string filename) = 0;
        virtual void printBroken(json dataJson, std::string filename) = 0;
        virtual void printIngest(json dataJson, std::string filename) = 0;
};


#endif //QUALITAIR_IOUTPUT_H
