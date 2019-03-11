//
// Created by vwallyn on 05/03/19.
//

#include "../include/SensorsCommand.h"
#include "../../ETL/include/ETL.h"
#include "../../View/include/OutputJSON.h"
#include "../../View/include/OutputCLI.h"
#include "../../View/include/OutputHTML.h"
#include "easylogging++.h"


SensorsCommand &SensorsCommand::operator=(SensorsCommand other) {
    swap(*this, other);
    return *this;
}

SensorsCommand::SensorsCommand(const SensorsCommand &other) {
    bbox = other.bbox;
}

SensorsCommand::SensorsCommand(BBox b, OutputArguments outputArguments) {
    if (!b.isNull()){
        bbox = b;
    }
}

SensorsCommand::~SensorsCommand() {

}

void SensorsCommand::execute() {
    json config;
    config["type"] = ETL::SENSOR;

    if(!bbox.isNull()){
        config["hasBBox"] = true;

        json bbox = this->bbox;
        config["BBox"] = bbox;
    }
    else{
        config["hasBBox"] = false;
    }

    config["hasStart"] = false;
    config["hasEnd"] = false;

    config["hasAttributes"] = false;
    config["hasSensors"] = false;

    IETL& etl = ETL::getInstance();
    std::vector<Sensor*> result = * (std::vector<Sensor*>*) etl.getData(config);

    // no dataprocesor treatment

    // transform result in json here (because no data processor treatment)
    json res = json::array();
    for (const Sensor* ptrSensor : result){
        res.push_back(*ptrSensor);
    }

    if (outputArguments.outputFormat == OutputFormat::HUMAN){
        OutputCLI::getInstance().printStats(res);
    }
    else if(outputArguments.outputFormat == OutputFormat::JSON){
        OutputJSON::getInstance().printStats(res, outputArguments.outputFile);
    }
    else{ // OutputFormat::HTML
        OutputHTML::getInstance().printStats(res, outputArguments.outputFile);
    }
    //LOG(INFO) << res;

}

void swap(SensorsCommand &first, SensorsCommand &second) {
    std::swap(first.bbox, second.bbox);
}

void SensorsCommand::to_json(json& j) const {
    j = json{
            {"command", "sensors"},
            {"bbox", bbox}
    };
}

void SensorsCommand::from_json(const json& j) {
    j.at("bbox").get_to(bbox);
}