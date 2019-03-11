//
//        ----[  QUALIT'AIR  ]----
//
//    Marsaud Menseau Thomasset Wallyn
//  Copyright © 2019 - All right reserved
//

#include "../include/StatsCommand.h"
#include "../../ETL/include/ETL.h"
#include "../../globals.h"
#include "../../View/include/OutputCLI.h"
#include "../../View/include/OutputJSON.h"
#include "../../View/include/OutputHTML.h"
#include "../../DataProcessor/include/DataProcessor.h"
#include "easylogging++.h"
#include "../../utils.h"
#include "../include/Cache.h"

const std::unordered_map<std::string, StatsCommand::StatEnum> StatsCommand::StatDictionary{
        {"AVG",       StatsCommand::AVG},
        {"EXTREMS",   StatsCommand::EXTREMS},
        {"DEVIATION", StatsCommand::DEVIATION},
        {"ATMO",      StatsCommand::ATMO}
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

StatsCommand::StatsCommand(StatEnum t, BBox b, time_t s, time_t e, std::vector<std::string> attr, std::vector<std::string> sen, OutputArguments outputArguments, json interpolationConfig)
        : Command(outputArguments), type(t), bbox(b), start(s), end(e), attributes(attr), sensors(sen), interpolationConfig(interpolationConfig) {
}

StatsCommand::~StatsCommand() {

}

void StatsCommand::execute() {
    json config;
    config["type"] = ETL::MEASURE;
    config["doInterpolation"] = true;
    if (!bbox.isNull()) {
        config["hasBBox"] = true;

        json bbox = this->bbox;
        config["BBox"] = bbox;
    } else {
        config["hasBBox"] = false;
    }

    if (start != 0) {
        config["hasStart"] = true;
        config["start"] = start;
    } else {
        config["hasStart"] = false;
    }

    if (end != 0) {
        config["hasEnd"] = true;
        config["end"] = end;
    } else {
        config["hasEnd"] = false;
    }

    if (!attributes.empty()) {
        config["hasAttributes"] = true;
        config["attributes"] = attributes;
    } else {
        config["hasAttributes"] = false;
    }

    if (!sensors.empty()) {
        config["hasSensors"] = true;
        config["sensors"] = sensors;
    } else {
        config["hasSensors"] = false;
    }
    config.merge_patch(interpolationConfig);

    IETL &etl = ETL::getInstance();
    IDataProcessor &dataProcessor = DataProcessor::getInstance();

    json res;
    if (type == StatEnum::ATMO) {
        if (!config["hasStart"] || !config["hasEnd"]) {
            LOG(WARNING) << "start and end must be specified for ATMO in Qualit'Air BETA";
            return;
        } else {
            for (long i = start; i <= end - 86400; i += 86400) {
                config["start"] = i;
                config["end"] = i + 86400;
                pointCollection *result = (pointCollection *) etl.getData(config);
                std::string date = utils::timestampToString(i);
                res[date] = (*dataProcessor.computeAtmo(*result))["atmo"];
            }
        }
    } else if (type == StatEnum::AVG) {
        if (!config["hasStart"] || !config["hasEnd"]) {
            LOG(WARNING) << "start and end must be specified to do process batching in Qualit'Air BETA";
            pointCollection *result = (pointCollection *) etl.getData(config);
            res = *dataProcessor.computeAverage(*result);
        } else {
            std::vector<std::pair<json, std::unordered_map<std::string, int>>> means;
            std::unordered_map<std::string, int> totalAttributesCount;

            for (long i = start; i <= end - 86400; i += 86400) {
                config["start"] = i;
                config["end"] = (i + 86400);
                pointCollection *result = (pointCollection *) etl.getData(config);
                std::unordered_map<std::string, int> attributesCount;
                for (auto i : *result) {
                    for (auto j : i) {
                        for (auto k : j) {
                            for (auto it : k) {
                                attributesCount[it.first]++;
                                totalAttributesCount[it.first]++;
                            }
                        }
                    }
                }
                means.push_back(std::make_pair(*dataProcessor.computeAverage(*result), attributesCount));
            }
            for (int i = 0; i < means.size(); i++) {
                for (auto&[key, value] : means[i].first.items()) {
                    if (i == 0) {
                        res[key] = 0.0;
                    }
                    res[key] = (double) res[key] + (double) means[i].first[key] * ((double) means[i].second[key] / totalAttributesCount[key]);
                }
            }

        }

    } else if (type == StatEnum::DEVIATION) {
        pointCollection *result = (pointCollection *) etl.getData(config);
        res = *dataProcessor.computeDeviation(*result);
        /* TODO in order to compute correct value, we need to also calculate the variation between the means
         * etc.. so it is not implemented right now
         *
         * if (!config["hasStart"] || !config["hasEnd"]) {
            LOG(WARNING) << "start and end must be specified to do process batching in Qualit'Air BETA";
            pointCollection* result = (pointCollection*) etl.getData(config);
            res = * dataProcessor.computeDeviation(* result);
        } else {
            std::vector<std::unordered_map<std::string, double>> deviations;
            double count = 0;
            for (long i = start; i <= end - 86400; i += 86400) {
                config["start"] = i;
                config["end"] = i + 86400;
                pointCollection *result = (pointCollection *) etl.getData(config);
                //LOG(DEBUG) << *dataProcessor.computeDeviation(*result);
                if (res.empty()) {
                    res = *dataProcessor.computeDeviation(*result);
                    for (auto& [key, value] : (*dataProcessor.computeDeviation(*result)).items()) {
                        res[key] = (double)pow(value, 2.0);
                    }
                } else {
                    for (auto& [key, value] : (*dataProcessor.computeDeviation(*result)).items()) {
                        res[key] = (double)res[key] + (double)pow(value, 2.0);
                    }
                }
                count++;
            }
            for (auto& [key, value] : res.items()) {
                res[key] = (double)res[key] / count;
                res[key] = sqrt((double)value);
            }
        }*/
    } else { // StatEnum::EXTREMS
        if (!config["hasStart"] || !config["hasEnd"]) {
            LOG(WARNING) << "start and end must be specified to do process batching in Qualit'Air BETA";
            pointCollection *result = (pointCollection *) etl.getData(config);
            res = *dataProcessor.computeExtrems(*result);
        } else {
            for (long i = start; i <= end - 86400; i += 86400) {
                config["start"] = i;
                config["end"] = i + 86400;
                pointCollection *result = (pointCollection *) etl.getData(config);
                if (res.empty()) {
                    res = *dataProcessor.computeExtrems(*result);
                } else {
                    for (auto&[key, value] : (*dataProcessor.computeExtrems(*result)).items()) {
                        if (res[key]["max"] < value["max"]) {
                            res[key]["max"] = value["max"];
                        }
                        if (res[key]["min"] > value["min"]) {
                            res[key]["min"] = value["min"];
                        }
                    }
                }
                LOG(DEBUG) << *dataProcessor.computeExtrems(*result);
            }
        }
    }

    if (config["hasStart"] && config["hasEnd"]) {
        Cache cache;
        cache.put(*this, res);
    }

    if (outputArguments.outputFormat == OutputFormat::HUMAN) {
        OutputCLI::getInstance().printStats(res);
    } else if (outputArguments.outputFormat == OutputFormat::JSON) {
        OutputJSON::getInstance().printStats(res, outputArguments.outputFile);
    } else { // OutputFormat::HTML
        OutputHTML::getInstance().printStats(res, outputArguments.outputFile);
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

void StatsCommand::to_json(json &j) const {
    j = json{
            {"command",    "stats"},
            {"type",       type},
            {"bbox",       bbox},
            {"start",      start},
            {"end",        end},
            {"attributes", attributes},
            {"sensors",    sensors}
    };
}

void StatsCommand::from_json(const json &j) {
    j.at("bbox").get_to(bbox);
    j.at("type").get_to(type);
    j.at("start").get_to(start);
    j.at("end").get_to(end);
    j.at("attribute").get_to(attributes);
    j.at("sensors").get_to(sensors);
}