//
// Created by Wallyn Valentin on 17/02/2019.
//

#include "../include/DetectBrokenCommand.h"
#include "../../ETL/include/ETL.h"
#include "../../View/include/OutputCLI.h"
#include "../../View/include/OutputHTML.h"
#include "../../View/include/OutputJSON.h"
#include "../../DataProcessor/include/DataProcessor.h"

DetectBrokenCommand &DetectBrokenCommand::operator=(DetectBrokenCommand other) {
    swap(*this, other);
    return *this;
}

void DetectBrokenCommand::execute() {
    json config;
    config["type"] = ETL::MEASURE;

    if(!this->bbox.isNull()){
        config["hasBBox"] = true;

        json bbox = this->bbox;
        config["BBox"] = bbox;
    }
    else{
        config["hasBBox"] = false;
    }

    if (this->start != 0){
        config["hasStart"] = true;
        config["start"] = this->start;
    }
    else{
        config["hasStart"] = false;
    }

    if (this->end != 0){
        config["hasEnd"] = true;
        config["end"] = this->end;
    }
    else{
        config["hasEnd"] = false;
    }

    if (!this->attributes.empty()){
        config["hasAttributes"] = true;
        config["attributes"] = this->attributes;
    }
    else{
        config["hasAttributes"] = false;
    }

    if (!this->sensors.empty()){
        config["hasSensors"] = true;
        config["sensors"] = this->sensors;
    }
    else{
        config["hasSensors"] = false;
    }

    IETL& etl = ETL::getInstance();
    std::vector<Measurement*> result = * (std::vector<Measurement*>*) etl.getData(config);

    IDataProcessor& dataProcessor = DataProcessor::getInstance();
    auto res = dataProcessor.detectBroken(result, brokenTime, admissibleRanges);

    if (this->outputArguments.outputFormat == OutputFormat::HUMAN){
        OutputCLI::getInstance().printBroken(*res);
    }
    else if(this->outputArguments.outputFormat == OutputFormat::JSON){
        OutputJSON::getInstance().printBroken(*res, this->outputArguments.outputFile);
    }
    else{
        OutputHTML::getInstance().printBroken(*res, this->outputArguments.outputFile);
    }
}


DetectBrokenCommand::DetectBrokenCommand(const DetectBrokenCommand &other) {
    bbox = other.bbox;
    start = other.start;
    end = other.end;
    attributes = other.attributes;
    sensors = other.sensors;
}

DetectBrokenCommand::DetectBrokenCommand(BBox box, time_t st, time_t e, std::vector<std::string> attr,
        std::vector<std::string> sens, int bT, std::unordered_map<std::string, std::pair<double ,double >> aR,
        OutputArguments outputArguments) : Command(outputArguments), bbox(box), start(st), end(e), attributes(attr),
        sensors(sens), brokenTime(bT), admissibleRanges(aR)
{

}

DetectBrokenCommand::~DetectBrokenCommand() {

}

void swap(DetectBrokenCommand &first, DetectBrokenCommand &second) {
    std::swap(first.bbox, second.bbox);
    std::swap(first.start, second.start);
    std::swap(first.end, second.end);
    std::swap(first.attributes, second.attributes);
    std::swap(first.sensors, second.sensors);
}

void DetectBrokenCommand::to_json(json& j) const {
    j = json{
        {"command", "broken"},
        {"bbox", bbox},
        {"start", start},
        {"end", end},
        {"attributes", attributes},
        {"sensors", sensors}
    };
}

void DetectBrokenCommand::from_json(const json& j) {
    j.at("bbox").get_to(bbox);
    j.at("start").get_to(start);
    j.at("end").get_to(end);
    j.at("attributes").get_to(attributes);
    j.at("sensors").get_to(sensors);
}