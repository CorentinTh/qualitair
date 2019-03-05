//
// Created by Wallyn Valentin on 17/02/2019.
//

#ifndef QUALITAIR_SPIKESCOMMAND_H
#define QUALITAIR_SPIKESCOMMAND_H


#include <vector>
#include "Command.h"
#include "../../Data/include/BBox.h"

class SpikesCommand : public Command {
    public:

        SpikesCommand & operator = ( SpikesCommand other );
        SpikesCommand ( const SpikesCommand & other );
        SpikesCommand ( std::string attribute, BBox bbox, time_t start, time_t end, std::vector<std::string> sensors );
        virtual ~SpikesCommand ( );

        void execute() override;

        void output() override;

    protected:
        friend void swap(SpikesCommand & first, SpikesCommand & second);

        std::string outputPath;
        BBox bbox;
        time_t start;
        time_t end;
        std::string attribute;
        std::vector<std::string> sensors;

};


#endif //QUALITAIR_SPIKESCOMMAND_H
