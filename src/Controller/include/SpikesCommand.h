//
// Created by Wallyn Valentin on 17/02/2019.
//

#ifndef QUALITAIR_SPIKESCOMMAND_H
#define QUALITAIR_SPIKESCOMMAND_H


#include <vector>
#include "Command.h"
#include "../../ETL/include/GeoFilter.h"

class SpikesCommand : public Command {
    public:

        SpikesCommand & operator = ( SpikesCommand other );
        SpikesCommand ( const SpikesCommand & other );
        SpikesCommand ( BBox bbox, time_t start, time_t end, std::vector<std::string> attributes, std::vector<int> sensors );
        virtual ~SpikesCommand ( );

        void execute() override;

        void output() override;

    protected:
        friend void swap(SpikesCommand & first, SpikesCommand & second);

    private:
        std::string outputPath;
        BBox bbox;
        time_t start;
        time_t end;
        std::vector<std::string> attributes;
        std::vector<int> sensors;

};


#endif //QUALITAIR_SPIKESCOMMAND_H
