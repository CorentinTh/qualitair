//
// Created by Wallyn Valentin on 17/02/2019.
//

#include <fstream>
#include <iostream>

#include "../include/OutputJSON.h"

OutputJSON::OutputJSON(){}

void OutputJSON::printSpikes(json dataJson, std::string filename) {
    // if the file existed, we overwrite it
    std::ofstream file(filename);
    if (file.is_open()){
        copyJsonToFile(dataJson, &file);
        file.close();
    }
    else{
        std::cout << "Erreur de manipulation du fichier " << filename << std::endl;
    }
}

void OutputJSON::printStats(json dataJson, std::string filename) {
    // if the file existed, we overwrite it
    std::ofstream file(filename);
    if (file.is_open()){
        copyJsonToFile(dataJson, &file);
        file.close();
    }
    else{
        std::cout << "Erreur de manipulation du fichier " << filename << std::endl;
    }
}

void OutputJSON::printSim(json dataJson, std::string filename) {
    // if the file existed, we overwrite it
    std::ofstream file(filename);
    if (file.is_open()){
        copyJsonToFile(dataJson, &file);
        file.close();
    }
    else{
        std::cout << "Erreur de manipulation du fichier " << filename << std::endl;
    }
}

void OutputJSON::printBroken(json dataJson, std::string filename) {
    // if the file existed, we overwrite it
    std::ofstream file(filename);
    if (file.is_open()){
        copyJsonToFile(dataJson, &file);
    }
    file.close();
}

void OutputJSON::printIngest(json dataJson, std::string filename) {
    // if the file existed, we overwrite it
    std::ofstream file(filename);
    if (file.is_open()){
        copyJsonToFile(dataJson, &file);
        file.close();
    }
    else{
        std::cout << "Erreur de manipulation du fichier " << filename << std::endl;
    }
}

void OutputJSON::copyJsonToFile(json data, std::ofstream * ptrFile){
    std::string s = data.dump(4); // indent with four spaces
    (*ptrFile) << s;
}
