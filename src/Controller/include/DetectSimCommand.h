//
//        ----[  QUALIT'AIR  ]----
//
//    Marsaud Menseau Thomasset Wallyn
//  Copyright © 2019 - All right reserved
//

#ifndef QUALITAIR_DETECTSIMCOMMAND_H
#define QUALITAIR_DETECTSIMCOMMAND_H

#include <vector>
#include "Command.h"
#include "../../Data/include/BBox.h"

class DetectSimCommand : public Command {
public:

    DetectSimCommand &operator=(DetectSimCommand other);

    DetectSimCommand(const DetectSimCommand &other);

    DetectSimCommand(BBox bbox, time_t start, time_t end, std::vector<std::string> attributes, std::vector<std::string> sensors, double threshold, OutputArguments outputArguments);

    virtual ~DetectSimCommand();

    void execute() override;


protected:
    friend void swap(DetectSimCommand &first, DetectSimCommand &second);

    virtual void to_json(json &j) const override;

    virtual void from_json(const json &j) override;

    double threshold;
    BBox bbox;
    time_t start;
    time_t end;
    std::vector<std::string> attributes;
    std::vector<std::string> sensors;
};


#endif //QUALITAIR_DETECTSIMCOMMAND_H
