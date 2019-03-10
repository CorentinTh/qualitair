//
// Created by Wallyn Valentin on 17/02/2019.
//

#include "../include/DetectSimCommand.h"
#include "../../ETL/include/ETL.h"
#include "../../DataProcessor/include/DataProcessor.h"
#include "../../View/include/OutputCLI.h"
#include "../../View/include/OutputJSON.h"
#include "../../View/include/OutputHTML.h"
#include "../include/Cache.h"

DetectSimCommand &DetectSimCommand::operator=(DetectSimCommand other) {
    swap(*this, other);
    return *this;
}

DetectSimCommand::DetectSimCommand(const DetectSimCommand &other) {
    bbox = other.bbox;
    start = other.start;
    end = other.end;
    attributes = other.attributes;
    sensors = other.sensors;
    threshold = other.threshold;
}

DetectSimCommand::DetectSimCommand(BBox b, time_t st, time_t e, std::vector<std::string> attr,
        std::vector<std::string> sen, double thresh, OutputArguments outputArguments) : Command(outputArguments), bbox(b), start(st), end(e), attributes(attr), sensors(sen),
        threshold(thresh) {
}

DetectSimCommand::~DetectSimCommand() {

}

void DetectSimCommand::execute() {
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

    if (!sensors.empty()){
        config["hasSensors"] = true;
        config["sensors"] = sensors;
    }
    else{
        config["hasSensors"] = false;
    }

    if (!attributes.empty()){
        config["hasAttributes"] = true;
        config["attributes"] = attributes;
    }
    else{
        config["hasAttributes"] = false;
    }

    IETL& etl = ETL::getInstance();
    IDataProcessor& dataProcessor = DataProcessor::getInstance();

    auto result = *((std::vector<Measurement*> *) etl.getData(config));

    json res = *dataProcessor.detectSimilar(result, threshold);

    if (config["hasEnd"]) {
        Cache cache;
        cache.put(*this, res);
    }

    if (outputArguments.outputFormat == OutputFormat::HUMAN){
        OutputCLI::getInstance().printSim(res);
    }
    else if(outputArguments.outputFormat == OutputFormat::JSON){
        OutputJSON::getInstance().printSim(res, outputArguments.outputFile);
    }
    else{ // OutputFormat::HTML
        OutputHTML::getInstance().printSim(res, outputArguments.outputFile);
    }
}


void swap(DetectSimCommand &first, DetectSimCommand &second) {
    std::swap(first.bbox, second.bbox);
    std::swap(first.start, second.start);
    std::swap(first.end, second.end);
    std::swap(first.attributes, second.attributes);
    std::swap(first.sensors, second.sensors);
    std::swap(first.threshold, second.threshold);
}

void DetectSimCommand::to_json(json& j) const {
    j = json{
            {"command", "similarities"},
            {"bbox", bbox},
            {"start", start},
            {"end", end},
            {"attributes", attributes},
            {"sensors", sensors},
            {"threshold", threshold}
    };
}

void DetectSimCommand::from_json(const json& j) {
    j.at("bbox").get_to(bbox);
    j.at("start").get_to(start);
    j.at("end").get_to(end);
    j.at("attributes").get_to(attributes);
    j.at("sensors").get_to(sensors);
    j.at("threshold").get_to(threshold);
}
