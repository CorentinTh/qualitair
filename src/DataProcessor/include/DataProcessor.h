//
// Created by Wallyn Valentin on 17/02/2019.
//

#ifndef QUALITAIR_DATAPROCESSOR_H
#define QUALITAIR_DATAPROCESSOR_H


#include "IDataProcessor.h"

class DataProcessor : public IDataProcessor {
    public:
        static DataProcessor& getInstance()
        {
            static DataProcessor instance;
            return instance;
        }

        DataProcessor(DataProcessor const&)       = delete;
        void operator=(DataProcessor const&)  = delete;
    
    private:
        DataProcessor() {}
};


#endif //QUALITAIR_DATAPROCESSOR_H
