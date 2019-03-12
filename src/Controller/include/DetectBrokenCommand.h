//
//        ----[  QUALIT'AIR  ]----
//
//    Marsaud Menseau Thomasset Wallyn
//  Copyright © 2019 - All right reserved
//

#ifndef QUALITAIR_DETECTBROKENCOMMAND_H
#define QUALITAIR_DETECTBROKENCOMMAND_H

#include <vector>
#include "Command.h"
#include "../../Data/include/BBox.h"

class DetectBrokenCommand : public Command {
public:

    DetectBrokenCommand &operator=(DetectBrokenCommand other);

    DetectBrokenCommand(const DetectBrokenCommand &other);

    DetectBrokenCommand(BBox bbox, time_t start, time_t end, std::vector<std::string> attributes,
                        std::vector<std::string> sensors, int brokenTime, std::unordered_map<std::string, std::pair<double, double>> admissibleRanges,
                        OutputArguments outputArguments);

    virtual ~DetectBrokenCommand();

    void execute() override;

protected:
    friend void swap(DetectBrokenCommand &first, DetectBrokenCommand &second);

    virtual void to_json(json &j) const override;

    virtual void from_json(const json &j) override;

    BBox bbox;
    time_t start;
    time_t end;
    std::vector<std::string> attributes;
    std::vector<std::string> sensors;
    int brokenTime;
    std::unordered_map<std::string, std::pair<double, double>> admissibleRanges;

};


#endif //QUALITAIR_DETECTBROKENCOMMAND_H
