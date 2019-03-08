#include "../include/StatsCommand.h"
#include "../../ETL/include/ETL.h"
#include "../../globals.h"
#include "../../View/include/OutputCLI.h"
#include "../../View/include/OutputJSON.h"
#include "../../View/include/OutputHTML.h"
#include "../../DataProcessor/include/DataProcessor.h"

const std::unordered_map<std::string, StatsCommand::StatEnum> StatsCommand::StatDictionary {
    {"AVG", StatsCommand::AVG}, {"EXTREMS", StatsCommand::EXTREMS}, {"DEVIATION", StatsCommand::DEVIATION}, {"ATMO", StatsCommand::ATMO}
};

StatsCommand &StatsCommand::operator=(StatsCommand other) {
    swap(*this, other);
    return *this;
}

StatsCommand::StatsCommand(const StatsCommand &other) {
    type = other.type;
    bbox = other.bbox;
    start = other.start;
    end = other.end;
    attributes = other.attributes;
    sensors = other.sensors;
}

StatsCommand::StatsCommand(StatEnum t, BBox b, time_t s, time_t e, std::vector<std::string> attr,
                           std::vector<std::string> sen, OutputArguments outputArguments) : Command(outputArguments), type(t), bbox(b), start(s), end(s), attributes(attr), sensors(sen) {
}

StatsCommand::~StatsCommand() {

}

void StatsCommand::execute() {
    // get data puis aggregation
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

    if (!this->attributes.empty()){
        config["hasSensors"] = true;
        config["sensors"] = this->sensors;
    }
    else{
        config["hasSensors"] = false;
    }

    ETL etl = ETL::getInstance();
    DataProcessor dataProcessor = DataProcessor::getInstance();

    pointCollection* result = (pointCollection*) etl.getData(config);

    json res;
    if (type == StatEnum::ATMO){
        res = * dataProcessor.computeAtmo(* result);
    }
    else if(type == StatEnum::AVG) {
        res = * dataProcessor.computeAverage(* result);
    }
    else if(type == StatEnum::DEVIATION){
        res = * dataProcessor.computeDeviation(* result);
    }
    else{ // StatEnum::EXTREMS
        res = * dataProcessor.computeExtrems(* result);
    }
    // todo cache res
    // if end start settled


    if (this->outputArguments.outputFormat == OutputFormat::HUMAN){
        OutputCLI::getInstance().printStats(res);
    }
    else if(this->outputArguments.outputFormat == OutputFormat::JSON){
        OutputJSON::getInstance().printStats(res, this->outputArguments.outputFile);
    }
    else{ // OutputFormat::HTML
        OutputHTML::getInstance().printStats(res, this->outputArguments.outputFile);
    }
}

void swap(StatsCommand &first, StatsCommand &second) {
    std::swap(first.type, second.type);
    std::swap(first.bbox, second.bbox);
    std::swap(first.start, second.start);
    std::swap(first.end, second.end);
    std::swap(first.attributes, second.attributes);
    std::swap(first.sensors, second.sensors);
}

void StatsCommand::to_json(json& j) const {
    j = json{
            {"command", "broken"},
            {"bbox", bbox},
            {"start", start},
            {"end", end},
            {"attribute", attributes},
            {"sensors", sensors}
    };
}

void StatsCommand::from_json(const json& j) {
    j.at("bbox").get_to(bbox);
    j.at("start").get_to(start);
    j.at("end").get_to(end);
    j.at("attribute").get_to(attributes);
    j.at("sensors").get_to(sensors);
}