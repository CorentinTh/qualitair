//
// Created by Wallyn Valentin on 17/02/2019.
//

#include "../include/ETL.h"
#include "../../Data/include/QueryBuilder.h"
#include <iostream>
#include <dirent.h>
#include <stdio.h>
#include <csvmonkey.hpp>

long ETL::ingest(std::string path) {
    for(std::string file : listCSVFiles(path)) {
        csvmonkey::MappedFileCursor cursor;
        cursor.open(file.c_str());

        csvmonkey::CsvReader reader(cursor);
        csvmonkey::CsvCursor &row = reader.row();
        reader.read_row();

        QueryBuilder queryBuilder;
        if(row.cells[0].as_str() == "AttributeId") {
            while(reader.read_row()) {

            }
        } else if(row.cells[0].as_str() == "SensorId") {

        } else if(row.cells[0].as_str() == "Timestamp") {

        } else {
            //TODO: not a interpratable csv file, error handling ?
        }
    }
}

std::vector<std::string> ETL::listCSVFiles(std::string path) {
    std::vector<std::string> files;
    DIR *dir;
    struct dirent *ent;

    if((dir = opendir(path.c_str())) != nullptr) {
        while((ent = readdir (dir)) != nullptr) {
            std::string fileName = ent->d_name;
            if(fileName.find(".csv") != std::string::npos) {
                files.push_back(fileName);
            }
        }
        closedir(dir);
    } else {
        //TODO: error handling ?
    }

    return files;
}

void ETL::getData() {

}