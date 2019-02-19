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
    
        virtual void printSpikes(std::string dataJson);
        virtual void printStats(std::string dataJson);
        virtual void printSim(std::string dataJson);
        virtual void printBroken(std::string dataJson);
        virtual void printIngest(std::string dataJson);
    
        OutputJSON(OutputJSON const&)       = delete;
        void operator=(OutputJSON const&)  = delete;
    
    private:
        OutputJSON();
};


#endif //QUALITAIR_OUTPUTJSON_H
