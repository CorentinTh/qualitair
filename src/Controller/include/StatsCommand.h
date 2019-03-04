//
// Created by Wallyn Valentin on 17/02/2019.
//

#ifndef QUALITAIR_STATSCOMMAND_H
#define QUALITAIR_STATSCOMMAND_H


#include <vector>
#include "Command.h"
#include "../../Data/include/BBox.h"

class StatsCommand : public Command {
    public:

        StatsCommand & operator = ( StatsCommand other );
        StatsCommand ( const StatsCommand & other );
        StatsCommand ( BBox bbox, time_t start, time_t end, std::vector<std::string> attributes, std::vector<int> sensors );
        virtual ~StatsCommand ( );

        void execute() override;

        void output() override;

protected:
        friend void swap(StatsCommand & first, StatsCommand & second);

private:
    BBox bbox;
    time_t start;
    time_t end;
    std::vector<std::string> attributes;
    std::vector<int> sensors;
};


#endif //QUALITAIR_STATSCOMMAND_H
