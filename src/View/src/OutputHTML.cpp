//
// Created by Wallyn Valentin on 17/02/2019.
//

#include "../include/OutputHTML.h"
#include <fstream>
#include <ctime>
#include <iostream>

void OutputHTML::printSpikes(json data, std::string filename) {
    fulfillHtmlTemplate(data, filename, "../html-templates/dist/spikes-template.html");
}

void OutputHTML::printStats(json data, std::string filename) {
    fulfillHtmlTemplate(data, filename, "../html-templates/dist/stats-template.html");
}

void OutputHTML::printSim(json data, std::string filename) {
    fulfillHtmlTemplate(data, filename, "../html-templates/dist/similar-template.html");
}

void OutputHTML::printBroken(json data, std::string filename) {
    fulfillHtmlTemplate(data, filename, "../html-templates/dist/broken-template.html");
}

void OutputHTML::printIngest(json data, std::string filename) {
    fulfillHtmlTemplate(data, filename, "../html-templates/dist/ingest-template.html");
}

void OutputHTML::printSensors(json data, std::string filename) {
    //fulfillHtmlTemplate(data, filename, "");
    // todo complete when sensors template is created
}

OutputHTML::OutputHTML() {

}

void OutputHTML::fulfillHtmlTemplate(json data, std::string filename, std::string srcTemplateHtml){
    std::ofstream htmlFile(filename);

    std::ifstream fileTemplate;

    fileTemplate.open(srcTemplateHtml, std::ifstream::in);

    if (fileTemplate.is_open()){
        if (htmlFile.is_open()){
            std::string line = "";
            while (std::getline(fileTemplate, line)){
                if (line == "$JSONPLACEHOLDER$"){
                    line = data.dump();
                }
                else if(line == "$DATEPLACEHOLDER$"){
                    int timestamp = (int) std::time(nullptr);
                    line = std::to_string(timestamp);
                }
                htmlFile << line;
            }
        }
    }

    htmlFile.close();
    fileTemplate.close();
}