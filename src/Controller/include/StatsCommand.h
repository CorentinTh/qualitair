//
//        ----[  QUALIT'AIR  ]----
//
//    Marsaud Menseau Thomasset Wallyn
//  Copyright © 2019 - All right reserved
//

#ifndef QUALITAIR_STATSCOMMAND_H
#define QUALITAIR_STATSCOMMAND_H

#include <vector>
#include "Command.h"
#include "../../Data/include/BBox.h"

class StatsCommand : public Command {
public:
    enum StatEnum {
        AVG, EXTREMS, DEVIATION, ATMO
    };
    static const std::unordered_map<std::string, StatEnum> StatDictionary;

    StatsCommand &operator=(StatsCommand other);

    StatsCommand(const StatsCommand &other);

    StatsCommand(StatEnum type, BBox bbox, time_t start, time_t end, std::vector<std::string> attributes,
                 std::vector<std::string> sensors, OutputArguments outputArguments, json interpolationConfig);

    virtual ~StatsCommand();

    void execute() override;

protected:
    friend void swap(StatsCommand &first, StatsCommand &second);

    virtual void to_json(json &j) const override;

    virtual void from_json(const json &j) override;

    StatEnum type;
    BBox bbox;
    time_t start;
    time_t end;
    std::vector<std::string> attributes;
    std::vector<std::string> sensors;
    json interpolationConfig;
};


#endif //QUALITAIR_STATSCOMMAND_H
