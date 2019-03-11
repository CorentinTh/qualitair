//
// Created by test on 17/02/2019.
//

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include "easylogging++.h"
#include "../include/OutputCLI.h"

OutputCLI::OutputCLI() {}

typedef struct {
    double x;
    double y;
    int tStart;
    int tEnd;
} Spike;

void OutputCLI::printSpikes(json data, std::string filename) {
    std::vector<Spike*> vectSpikes;
    if (!data.empty() && data.find("pics") != data.end()) {
        for (json::iterator it = data.at("pics")[0][0][0].begin(); it != data.at("pics")[0][0][0].end(); ++it){
            std::string actualType = it.key();
            LOG(INFO) << "Des pics de "<< actualType <<" ont été détectés :";

            double t0, x0, y0;
            int deltaS, deltaT;
            t0 = data.at("t0");
            x0 = data.at("x0");
            y0 = data.at("y0");
            deltaS = data.at("spatialStep");
            deltaT = data.at("temporalStep");

            int indiceT = 0; // time index
            for (const auto & timeList : data.at("pics")){
                int indiceY = 0; // longitude index
                for (const auto & y : timeList){
                    int indiceX = 0; // latitude index
                    for (const auto & x : y){
                        for (json::const_iterator itType = x.begin(); itType != x.end(); itType++){
                            std::string type = itType.key();
                            int value = itType.value();
                            if (actualType == type && value == 1) {
                                bool spikeInVector = false;
                                for (Spike* s : vectSpikes) {
                                    if (s->x == x0 + indiceX * deltaS
                                        && s->y == y0 + indiceY * deltaS) {
                                        if (s->tStart < (int) t0 + indiceT * deltaT
                                            && s->tEnd == (int) t0 + (indiceT - 1) * deltaT) {
                                            // if the spike is already in the spikes vector
                                            // we extend its duration
                                            s->tEnd = (int) t0 + (indiceT) * deltaT;
                                            spikeInVector = true;
                                        }
                                        else {
                                            spikeInVector = false;
                                        }
                                    }
                                }
                                if (!spikeInVector) {
                                    // if the spike is not in the spikes vector
                                    // we create it and add it
                                    Spike * newSpike = new Spike;
                                    newSpike->tEnd = (int) t0 + (indiceT) * deltaT;
                                    newSpike->tStart = (int) t0 + (indiceT) * deltaT;
                                    newSpike->x = x0 + indiceX * deltaS;
                                    newSpike->y = y0 + indiceY * deltaS;
                                    vectSpikes.push_back(newSpike);
                                }
                            }
                        }
                        indiceX++;
                    }
                    indiceY++;
                }
                indiceT++;
            }

            for (Spike * s : vectSpikes) {

                time_t tEnd = (time_t) s->tEnd;
                struct tm *tmEnd = localtime(&tEnd);
                char dateEnd[25];
                strftime(dateEnd, sizeof(dateEnd), "%H:%M:%S le %d/%m/%Y", tmEnd);

                time_t tStart = (time_t) s->tStart;
                struct tm *tmStart = localtime(&tStart);
                char dateStart[25];
                strftime(dateStart, sizeof(dateStart), "%H:%M:%S le %d/%m/%Y", tmStart);

                LOG(INFO) << " - en position (" << s->x << "," << s->y << ")" << " entre " << dateStart << " et " << dateEnd;

                // delete the pointers
                delete(s);
            }
        }
    }
}

void OutputCLI::printStats(json data, std::string filename) {
    if (!data.empty()){
        if(data.find("atmo") != data.end()){
            LOG(INFO) << "Résultat des analyses";
            int val = data.at("atmo");
            LOG(INFO) << "ATMO : " << val;
        }
        else if(data.find("avg") != data.end()){
            LOG(INFO) << "Résultat des analyses";
            LOG(INFO) << "Moyennes :";
            std::string attribute;
            double moyenne;
            for (json::iterator it = data.begin(); it != data.end(); ++it) {
                if (it.key() != "avg"){
                    attribute = it.key();
                    moyenne = it.value();
                    LOG(INFO) << " - " << attribute << " :" << moyenne;
                }
            }
        }
        else if(data.find("dev") != data.end()){
            LOG(INFO) << "Résultat des analyses";
            LOG(INFO) << "Ecart-types :";
            std::string attribute;
            double deviation;
            for (json::iterator it = data.begin(); it != data.end(); ++it) {
                if (it.key() != "dev"){
                    attribute = it.key();
                    deviation = it.value();
                    LOG(INFO) << " - " << attribute << " :" << deviation;
                }
            }
        }
        else if(data.find("ext") != data.end()){
            LOG(INFO) << "Résultat des analyses";
            LOG(INFO) << "Minimums et maximums :";
            std::string attribute;
            double minimum, maximum;
            for (json::iterator it = data.begin(); it != data.end(); ++it) {
                if (it.key() != "ext"){
                    attribute = it.key();
                    minimum = it.value().at("min");
                    maximum = it.value().at("max");
                    LOG(INFO) << " - " << attribute << " :";
                    LOG(INFO) << "    min :" << minimum;
                    LOG(INFO) << "    max :" << minimum;
                }
            }
        }
    }
}

void OutputCLI::printSim(json data, std::string filename) {
    if (!data.empty()){
        for (const auto & listSimilarSensors : data){
            LOG(INFO) << "------";
            LOG(INFO) << "Les capteurs suivants sont similaires :";
            double latitude, longitude;
            std::string description, id;
            for (const auto & sensor : listSimilarSensors){
                id = sensor.at("id");
                latitude = sensor.at("lat");
                longitude = sensor.at("long");
                description = sensor.at("description");

                LOG(INFO) << " - Capteur " << id << " : positionné en (" << std::to_string(latitude) << "," <<  std::to_string(longitude) << ")";
                LOG(INFO) << "   Description : " << description;
            }
        }
        LOG(INFO) << "------";
    }
}

void OutputCLI::printBroken(json data, std::string filename) {
    if (!data.empty()){
        LOG(INFO) << "Les capteurs suivants sont en panne :";
        for (json::iterator itSensor = data.begin(); itSensor != data.end(); ++itSensor) {
            double latitude, longitude;
            std::string description, id;
            id = (*itSensor).at("sensor").at("id");
            latitude = (*itSensor).at("sensor").at("lat");
            longitude = (*itSensor).at("sensor").at("long");
            description = (*itSensor).at("sensor").at("description");

            time_t tEnd = (time_t) (*itSensor).at("end");
            struct tm *tmEnd = localtime(&tEnd);
            char dateEnd[25];
            strftime(dateEnd, sizeof(dateEnd), "%H:%M:%S le %d/%m/%Y", tmEnd);

            time_t tStart = (time_t) (*itSensor).at("start");
            struct tm *tmStart = localtime(&tStart);
            char dateStart[25];
            strftime(dateStart, sizeof(dateStart), "%H:%M:%S le %d/%m/%Y", tmStart);

            LOG(INFO) << " - Capteur " << id << " : positionné en (" << std::to_string(latitude) << "," << std::to_string(longitude) << ")" << " entre " << dateStart << " et " << dateEnd;
            LOG(INFO) << "   Description : " << description;
        }
    }
}

void OutputCLI::printIngest(json data, std::string filename) {
    if (!data.empty()) {
        long output = data["lines"];
        if (output == 0) {
            LOG(WARNING) << "No element could not be inserted";
        } else if (output == -1) {
            LOG(ERROR) << "File is not properly formatted";
        } else {
            LOG(INFO) << output << " elements inserted successfully !";
        }
    }
}

