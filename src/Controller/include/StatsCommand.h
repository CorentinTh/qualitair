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
        enum StatEnum { AVG, EXTREMS, DEVIATION, ATMO };

        StatsCommand & operator = ( StatsCommand other );
        StatsCommand ( const StatsCommand & other );
        StatsCommand ( StatEnum type, BBox bbox, time_t start, time_t end, std::vector<std::string> attributes,
                std::vector<std::string> sensors );
        virtual ~StatsCommand ( );

        void execute() override;

    protected:
        friend void swap(StatsCommand & first, StatsCommand & second);
        friend void to_json(json& j, const StatsCommand& command);
        friend void from_json(const json& j, StatsCommand& command);

        StatEnum type;
        BBox bbox;
        time_t start;
        time_t end;
        std::vector<std::string> attributes;
        std::vector<std::string> sensors;
};


#endif //QUALITAIR_STATSCOMMAND_H
