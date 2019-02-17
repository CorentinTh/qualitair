//
// Created by Wallyn Valentin on 17/02/2019.
//

#ifndef QUALITAIR_IOUTPUT_H
#define QUALITAIR_IOUTPUT_H


class IOutput {
    public:
        virtual ~IOutput() {}
        virtual void printSpikes() = 0;
        virtual void printStats() = 0;
        virtual void printSim() = 0;
        virtual void printBroken() = 0;
        virtual void printIngest() = 0;
};


#endif //QUALITAIR_IOUTPUT_H
