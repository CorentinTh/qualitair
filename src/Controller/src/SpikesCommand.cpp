//
// Created by Wallyn Valentin on 17/02/2019.
//

#include "../include/SpikesCommand.h"
#include "../../ETL/include/ETL.h"
#include "../../globals.h"
#include "../../DataProcessor/include/DataProcessor.h"
#include "../../View/include/OutputCLI.h"
#include "../../View/include/OutputJSON.h"
#include "../../View/include/OutputHTML.h"

SpikesCommand &SpikesCommand::operator=(SpikesCommand other) {
    swap(*this, other);
    return *this;
}

SpikesCommand::SpikesCommand(const SpikesCommand &other) {
    attribute = other.attribute;
    bbox = other.bbox;
    start = other.start;
    end = other.end;
    sensors = other.sensors;
}

SpikesCommand::SpikesCommand(std::string attr, BBox b, time_t s, time_t e, std::vector<std::string> sen, SpikeDetectionConfiguration config, OutputArguments outputArguments) : Command(outputArguments), attribute(attr),
        bbox(b), start(s), end(s), sensors(sen), detectionConfig(config)
{

}

SpikesCommand::~SpikesCommand() {

}

void SpikesCommand::execute() {
    json config;
    config["type"] = ETL::MEASURE;

    if(!bbox.isNull()){
        config["hasBBox"] = true;

        json bbox = this->bbox;
        config["BBox"] = bbox;
    }
    else{
        config["hasBBox"] = false;
    }

    if (start != 0){
        config["hasStart"] = true;
        config["start"] = start;
    }
    else{
        config["hasStart"] = false;
    }

    if (end != 0){
        config["hasEnd"] = true;
        config["end"] = end;
    }
    else{
        config["hasEnd"] = false;
    }

    if (!attribute.empty()){
        config["hasAttributes"] = true;
        config["attributes"] = {attribute};
    }
    else{
        config["hasAttributes"] = false;
    }

    if (!this->sensors.empty()){
        config["hasSensors"] = true;
        config["sensors"] = sensors;
    }
    else{
        config["hasSensors"] = false;
    }

    IETL& etl = ETL::getInstance();
    IDataProcessor& dataProcessor = DataProcessor::getInstance();

    pointCollection * result = (pointCollection *) etl.getData(config);
    json res = * dataProcessor.detectSpikes(result, attribute, detectionConfig.valueThreshold,
            detectionConfig.timeThreshold, detectionConfig.areaThreshold);

    if (outputArguments.outputFormat == OutputFormat::HUMAN){
        OutputCLI::getInstance().printSpikes(res);
    }
    else if(outputArguments.outputFormat == OutputFormat::JSON){
        OutputJSON::getInstance().printSpikes(res, outputArguments.outputFile);
    }
    else{
        OutputHTML::getInstance().printSpikes(res, outputArguments.outputFile);
    }
}


void swap(SpikesCommand &first, SpikesCommand &second) {
    std::swap(first.bbox, second.bbox);
    std::swap(first.start, second.start);
    std::swap(first.end, second.end);
    std::swap(first.attribute, second.attribute);
    std::swap(first.sensors, second.sensors);
}

void SpikesCommand::to_json(json& j) const {
    j = json{
            {"command", "broken"},
            {"bbox", bbox},
            {"start", start},
            {"end", end},
            {"attribute", attribute},
            {"sensors", sensors}
    };
}

void SpikesCommand::from_json(const json& j) {
    j.at("bbox").get_to(bbox);
    j.at("start").get_to(start);
    j.at("end").get_to(end);
    j.at("attribute").get_to(attribute);
    j.at("sensors").get_to(sensors);
}
