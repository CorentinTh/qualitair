//
// Created by test on 17/02/2019.
//

#include <iostream>
#include <iomanip>
#include <vector>
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
        std::cout << "Des pics ont été détectés :" << std::endl;
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
                    if (x == 1) {
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

            std::cout << std::setprecision(8);
            std::cout << " - en position (" << s->x << "," << s->y << ")";
            std::cout << " entre " << dateStart << " et " << dateEnd << std::endl;

            // delete the pointers
            delete(s);
        }
    }
}

void OutputCLI::printStats(json data, std::string filename) {
    if (!data.empty()){
        if(data.find("atmo") != data.end()){
            std::cout << "Résultats des analyses :" << std::endl;
            std::cout << " - ATMO :" << std::endl;
            for (json::iterator it = data.at("atmo").begin(); it != data.at("atmo").end(); ++it){
                int date = std::stoi(it.key());
                int indiceAtmo = it.value();
                time_t tDate = (time_t) date;
                struct tm *tmDate = localtime(&tDate);
                char dateChar[12];
                strftime(dateChar, sizeof(dateChar), "%d/%m/%Y", tmDate);
                std::cout << "     " << dateChar << " : " << indiceAtmo << std::endl;
            }
            std::string attribute;
            double min, max, avg, deviation;
            for (json::iterator it = data.begin(); it != data.end(); ++it) {
                if (it.key() != "atmo"){
                    attribute = it.key();
                    min = it.value().at("min");
                    max = it.value().at("max");
                    avg = it.value().at("avg");
                    deviation = it.value().at("deviation");

                    std::cout << " - " << attribute << " :" << std::endl;
                    std::cout << "     avg : " << avg << std::endl;
                    std::cout << "     min : " << min << std::endl;
                    std::cout << "     max : " << max << std::endl;
                    std::cout << "     deviation : " << deviation << std::endl;
                }
            }
        }
    }
}

void OutputCLI::printSim(json data, std::string filename) {
    if (!data.empty()){
        for (json::iterator it = data.begin(); it != data.end(); ++it) {
            std::cout << "------" << std::endl;
            std::cout << "Les capteurs suivants sont similaires :" << std::endl;
            int id;
            double latitude, longitude;
            std::string description;
            for (json::iterator itSubList = (*it).begin(); itSubList != (*it).end(); ++itSubList){
                id = (*itSubList).at("id");
                latitude = (*itSubList).at("lat");
                longitude = (*itSubList).at("long");
                description = (*itSubList).at("description");

                std::cout << std::setprecision(9); // TODO a affiner en fonction des donnees fournies
                std::cout << " - Capteur n°" << id << " : positionné en (" << latitude << "," << longitude << ")" << std::endl;
                std::cout << "   Description : " << description << std::endl;
            }
        }
        std::cout << "------" << std::endl;
    }
}

void OutputCLI::printBroken(json data, std::string filename) {
    if (!data.empty()){
        std::cout << "Les capteurs suivants sont en panne :" << std::endl;
        for (json::iterator it = data.begin(); it != data.end(); ++it) {
            int id;
            double latitude, longitude;
            std::string description;
            id = (*it).at("id");
            latitude = (*it).at("lat");
            longitude = (*it).at("long");
            description = (*it).at("description");

            std::cout << std::setprecision(9); // TODO a affiner en fonction des donnees fournies
            std::cout << " - Capteur n°" << id << " : positionné en (" << latitude << "," << longitude << ")" << std::endl;
            std::cout << "   Description : " << description << std::endl;
        }
    }
}

void OutputCLI::printIngest(json data, std::string filename) {
    if (!data.empty()){
        if (data.find("error") != data.end()
                && data.find("lines_inserted") != data.end()){
            if (!data.at("error").empty()){
                int nbLinesInserted = data.at("lines_inserted");
                std::cout << std::to_string(nbLinesInserted) << " lignes ont été insérées avec succès" << std::endl;
            }
            else{
                std::cout << "Erreur :" << std::endl;
                std::cout << data.at("error") << std::endl;
            }
        }
    }
}

