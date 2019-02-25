//
// Created by Wallyn Valentin on 17/02/2019.
//

#ifndef QUALITAIR_SPIKESCOMMAND_H
#define QUALITAIR_SPIKESCOMMAND_H


#include "Command.h"

class SpikesCommand : public Command {
    public:

        SpikesCommand & operator = ( SpikesCommand other );
        SpikesCommand ( const SpikesCommand & other );
        SpikesCommand ( );
        virtual ~SpikesCommand ( );

        void execute() override;

        void output() override;

protected:
        friend void swap(SpikesCommand & first, SpikesCommand & second);
};


#endif //QUALITAIR_SPIKESCOMMAND_H
