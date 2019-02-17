//
// Created by Wallyn Valentin on 17/02/2019.
//

#ifndef QUALITAIR_DETECTSIMCOMMAND_H
#define QUALITAIR_DETECTSIMCOMMAND_H


#include "Command.h"

class DetectSimCommand : public Command {
    public:

        DetectSimCommand & operator = ( DetectSimCommand other );
        DetectSimCommand ( const DetectSimCommand & other );
        DetectSimCommand ( );
        virtual ~DetectSimCommand ( );

        void execute() override;

        void output() override;

protected:
        friend void swap(DetectSimCommand & first, DetectSimCommand & second);
};


#endif //QUALITAIR_DETECTSIMCOMMAND_H
