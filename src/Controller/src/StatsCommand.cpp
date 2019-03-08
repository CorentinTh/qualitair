#include "../include/StatsCommand.h"
#include "../../ETL/include/ETL.h"
#include "../../globals.h"
#include "../../DataProcessor/include/ATMOComputer.h"
#include "../../DataProcessor/include/Average.h"
#include "../../DataProcessor/include/Deviation.h"
#include "../../DataProcessor/include/Extrems.h"
#include "../../View/include/OutputCLI.h"
#include "../../View/include/OutputJSON.h"
#include "../../View/include/OutputHTML.h"

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
    pointCollection* result = (pointCollection*) etl.getData(config);

    json res;

    if (this->type == StatEnum::ATMO){
        ATMOComputer atmoComputer(* result);
        res = *atmoComputer.apply();
    }
    else if(this->type == StatEnum::AVG){
        Average averageComputer(*result);
        res = *averageComputer.apply();
    }
    else if(this->type == StatEnum::DEVIATION){
        Deviation deviationComputer(*result);
        res = *deviationComputer.apply();
    }
    else{ // StatEnum::EXTREMS
        Extrems extremsComputer(*result);
        res = *extremsComputer.apply();
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