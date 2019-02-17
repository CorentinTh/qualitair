//
// Created by Wallyn Valentin on 17/02/2019.
//

#ifndef QUALITAIR_DETECTBROKENCOMMAND_H
#define QUALITAIR_DETECTBROKENCOMMAND_H


#include "Command.h"

class DetectBrokenCommand : public Command {
    public:

        DetectBrokenCommand & operator = ( DetectBrokenCommand other );
        DetectBrokenCommand ( const DetectBrokenCommand & other );
        DetectBrokenCommand ( );
        virtual ~DetectBrokenCommand ( );

        void execute() override;

        void output() override;

protected:
        friend void swap(DetectBrokenCommand & first, DetectBrokenCommand & second);
};


#endif //QUALITAIR_DETECTBROKENCOMMAND_H
