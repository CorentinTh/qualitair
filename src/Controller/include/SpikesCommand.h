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
    struct SpikeDetectionConfiguration {
        double valueThreshold;
        unsigned int timeThreshold;
        unsigned int areaThreshold;
    };

    SpikesCommand &operator=(SpikesCommand other);

    SpikesCommand(const SpikesCommand &other);

    SpikesCommand(std::string attribute, BBox bbox, time_t start, time_t end, std::vector<std::string> sensors,
                  SpikeDetectionConfiguration config, OutputArguments outputArguments, json interpolationConfig);

    virtual ~SpikesCommand();

    void execute() override;


protected:
    friend void swap(SpikesCommand &first, SpikesCommand &second);

    virtual void to_json(json &j) const override;

    virtual void from_json(const json &j) override;

    std::string outputPath;
    BBox bbox;
    time_t start;
    time_t end;
    std::string attribute;
    std::vector<std::string> sensors;
    SpikeDetectionConfiguration detectionConfig;
    json interpolationConfig;

};


#endif //QUALITAIR_SPIKESCOMMAND_H
