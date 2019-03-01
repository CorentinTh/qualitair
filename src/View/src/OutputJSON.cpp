//
// Created by Wallyn Valentin on 17/02/2019.
//

#include <fstream>
#include <iostream>

#include "../include/OutputJSON.h"

OutputJSON::OutputJSON(){}

void OutputJSON::printSpikes(json data, std::string filename) {
    // if the file existed, we overwrite it
    std::ofstream file(filename);
    if (file.is_open()){
        copyJsonToFile(data, &file);
        file.close();
    }
    else{
        std::cout << "Erreur de manipulation du fichier " << filename << std::endl;
    }
}

void OutputJSON::printStats(json data, std::string filename) {
    // if the file existed, we overwrite it
    std::ofstream file(filename);
    if (file.is_open()){
        copyJsonToFile(data, &file);
        file.close();
    }
    else{
        std::cout << "Erreur de manipulation du fichier " << filename << std::endl;
    }
}

void OutputJSON::printSim(json data, std::string filename) {
    // if the file existed, we overwrite it
    std::ofstream file(filename);
    if (file.is_open()){
        copyJsonToFile(data, &file);
        file.close();
    }
    else{
        std::cout << "Erreur de manipulation du fichier " << filename << std::endl;
    }
}

void OutputJSON::printBroken(json data, std::string filename) {
    // if the file existed, we overwrite it
    std::ofstream file(filename);
    if (file.is_open()){
        copyJsonToFile(data, &file);
    }
    file.close();
}

void OutputJSON::printIngest(json data, std::string filename) {
    // if the file existed, we overwrite it
    std::ofstream file(filename);
    if (file.is_open()){
        copyJsonToFile(data, &file);
        file.close();
    }
    else{
        std::cout << "Erreur de manipulation du fichier " << filename << std::endl;
    }
}

void OutputJSON::copyJsonToFile(json data, std::ofstream * ptrFile) {
    std::string s = data.dump(4); // indent with four spaces
    (*ptrFile) << s;
}
