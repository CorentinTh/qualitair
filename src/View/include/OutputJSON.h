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
    
        virtual void printSpikes(json dataJsonn, std::string filename);
        virtual void printStats(json dataJsonn, std::string filename);
        virtual void printSim(json dataJsonn, std::string filename);
        virtual void printBroken(json dataJsonn, std::string filename);
        virtual void printIngest(json dataJsonn, std::string filename);
    
        OutputJSON(OutputJSON const&)       = delete;
        void operator=(OutputJSON const&)  = delete;
    
    private:
        OutputJSON();
};


#endif //QUALITAIR_OUTPUTJSON_H
