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
    
        virtual void printSpikes();
        virtual void printStats();
        virtual void printSim();
        virtual void printBroken();
        virtual void printIngest();
    
        OutputJSON(OutputJSON const&)       = delete;
        void operator=(OutputJSON const&)  = delete;
    
    private:
        OutputJSON() {}
};


#endif //QUALITAIR_OUTPUTJSON_H
