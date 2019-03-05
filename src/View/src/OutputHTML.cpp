//
// Created by Wallyn Valentin on 17/02/2019.
//

#include "../include/OutputHTML.h"
#include <fstream>
#include <ctime>

void OutputHTML::printSpikes(json data, std::string filename) {
    fulfillHtmlTemplate(data, filename);
}

void OutputHTML::printStats(json data, std::string filename) {
    fulfillHtmlTemplate(data, filename);
}

void OutputHTML::printSim(json data, std::string filename) {
    fulfillHtmlTemplate(data, filename);
}

void OutputHTML::printBroken(json data, std::string filename) {
    fulfillHtmlTemplate(data, filename);
}

void OutputHTML::printIngest(json data, std::string filename) {
    fulfillHtmlTemplate(data, filename);
}

OutputHTML::OutputHTML() {

}

void OutputHTML::fulfillHtmlTemplate(json data, std::string filename){
    std::ofstream htmlFile(filename);

    std::string filenameTemplate = "~/.qualitair/html-templates/spikes-templates.html";
    std::ifstream fileTemplate(filenameTemplate);
    std::string line = "";
    while (getline(fileTemplate, line)){
        if (line == "$DATA_PLACEHOLDER$"){
            line = data.dump();
        }
        else if(line == "$TIMESTAMP_PLACEHOLDER$"){
            int timestamp = (int) std::time(nullptr);
            line = std::to_string(timestamp);
        }
        htmlFile << line;
    }
    htmlFile.close();
    fileTemplate.close();
}
