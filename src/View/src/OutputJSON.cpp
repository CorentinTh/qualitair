//
// Created by Wallyn Valentin on 17/02/2019.
//

#include <fstream>
#include <iostream>

#include "../include/OutputJSON.h"

OutputJSON::OutputJSON(){}

void OutputJSON::printSpikes(json data, std::string filename) {
    printAnyData(data, filename);
}

void OutputJSON::printStats(json data, std::string filename) {
    printAnyData(data, filename);
}

void OutputJSON::printSim(json data, std::string filename) {
    printAnyData(data, filename);
}

void OutputJSON::printBroken(json data, std::string filename) {
    printAnyData(data, filename);
}

void OutputJSON::printIngest(json data, std::string filename) {
    printAnyData(data, filename);
}

void OutputJSON::copyJsonToFile(json data, std::ofstream * ptrFile) {
    std::string s = data.dump(4); // indent with four spaces
    (*ptrFile) << s;
}

void OutputJSON::putJsonInStdout(json data){
    std::cout << data.dump(4);
}

void OutputJSON::printAnyData(json data, std::string filename){
    if (filename == "stdout"){
        putJsonInStdout(data);
    }
    else{
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
}