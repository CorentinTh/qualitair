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

    virtual void printSpikes(json data, std::string filename);
    virtual void printStats(json data, std::string filename);
    virtual void printSim(json data, std::string filename);
    virtual void printBroken(json data, std::string filename);
    virtual void printIngest(json data, std::string filename);
    virtual void printSensors(json data, std::string filename);

    OutputHTML(OutputHTML const&)       = delete;
    void operator=(OutputHTML const&)  = delete;

private:
    OutputHTML();
    void fulfillHtmlTemplate(json data, std::string filename, std::string srcTemplateHtml);
};


#endif //QUALITAIR_OUTPUTHTML_H
