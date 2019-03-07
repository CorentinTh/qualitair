//
// Created by Wallyn Valentin on 17/02/2019.
//

#ifndef QUALITAIR_INGESTCOMMAND_H
#define QUALITAIR_INGESTCOMMAND_H


#include "Command.h"

class IngestCommand : public Command{
    public:

        IngestCommand & operator = ( IngestCommand other );
        IngestCommand ( const IngestCommand & other );
        IngestCommand ( std::string input );
        virtual ~IngestCommand ( );

        void execute() override;

    protected:
        friend void swap(IngestCommand & first, IngestCommand & second);

        std::string input;
};


#endif //QUALITAIR_INGESTCOMMAND_H
