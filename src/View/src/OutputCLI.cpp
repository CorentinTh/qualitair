//
// Created by test on 17/02/2019.
//

#include <iostream>
#include <iomanip>
#include "../include/OutputCLI.h"

OutputCLI::OutputCLI() {}

void OutputCLI::printSpikes(json dataJson, std::string filename) {

}

void OutputCLI::printStats(json dataJson, std::string filename) {
    if (!dataJson.empty()){
        if(dataJson.find("igqa") != dataJson.end()){
            std::cout << "Résultats des analyses :" << std::endl;
            std::cout << " - igqa : ";
            std::cout << dataJson.at("igqa").get<double>() << std::endl;
            std::string attribute;
            double min, max, avg, deviation;
            for (json::iterator it = dataJson.begin(); it != dataJson.end(); ++it) {
                if (it.key() != "igqa"){
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

void OutputCLI::printSim(json dataJson, std::string filename) {
    if (!dataJson.empty()){
        for (json::iterator it = dataJson.begin(); it != dataJson.end(); ++it) {
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

void OutputCLI::printBroken(json dataJson, std::string filename) {
    if (!dataJson.empty()){
        std::cout << "Les capteurs suivants sont en panne :" << std::endl;
        for (json::iterator it = dataJson.begin(); it != dataJson.end(); ++it) {
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

void OutputCLI::printIngest(json dataJson, std::string filename) {
    if (!dataJson.empty()){
        if (dataJson.find("error") != dataJson.end()
                && dataJson.find("lines_inserted") != dataJson.end()){
            if (!dataJson.at("error").empty()){
                int nbLinesInserted = dataJson.at("lines_inserted");
                std::cout << std::to_string(nbLinesInserted) << " lignes ont été insérées avec succès" << std::endl;
            }
            else{
                std::cout << "Erreur :" << std::endl;
                std::cout << dataJson.at("error") << std::endl;
            }
        }
    }
}

