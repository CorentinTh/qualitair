//
// Created by Wallyn Valentin on 17/02/2019.
//

#ifndef QUALITAIR_OUTPUTJSON_H
#define QUALITAIR_OUTPUTJSON_H


#include "IOutput.h"

class OutputJSON : public IOutput{
    public:
        static OutputJSON& getInstance()
        {
            static OutputJSON instance;
            return instance;
        }
    
        virtual void printSpikes(json data, std::string filename);
        virtual void printStats(json data, std::string filename);
        virtual void printSim(json data, std::string filename);
        virtual void printBroken(json data, std::string filename);
        virtual void printIngest(json data, std::string filename);
    
        OutputJSON(OutputJSON const&)       = delete;
        void operator=(OutputJSON const&)  = delete;
    
    private:
        OutputJSON();
        void copyJsonToFile(json data, std::ofstream * ptrFile);
        void putJsonInStdout(json data);
        void printAnyData(json data, std::string filename);

    };


#endif //QUALITAIR_OUTPUTJSON_H
