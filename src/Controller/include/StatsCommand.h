//
// Created by Wallyn Valentin on 17/02/2019.
//

#ifndef QUALITAIR_STATSCOMMAND_H
#define QUALITAIR_STATSCOMMAND_H


#include "Command.h"

class StatsCommand : public Command {
    public:

        StatsCommand & operator = ( StatsCommand other );
        StatsCommand ( const StatsCommand & other );
        StatsCommand ( );
        virtual ~StatsCommand ( );

        void execute() override;

        void output() override;

protected:
        friend void swap(StatsCommand & first, StatsCommand & second);
};


#endif //QUALITAIR_STATSCOMMAND_H
