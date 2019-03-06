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

        int dataType = -1;
        if(row.cells[0].as_str() == "AttributeId") dataType = ATTRIBUTE;
        else if(row.cells[0].as_str() == "SensorId") dataType = SENSOR;
        else if(row.cells[0].as_str() == "Timestamp") dataType = MEASURE;
        else {
            //TODO: not a interpretable csv file, error handling ?
        }

        int nbRows = 0;
        QueryBuilder queryBuilder;

        while(reader.read_row()) {
            if(nbRows == NB_ROW_PER_BATCH) {
                queryBuilder.execute();

                queryBuilder = QueryBuilder();
                nbRows = 0;
            }

            if(nbRows == 0) {
                if(dataType == ATTRIBUTE) {
                    queryBuilder.insert("Attribute").values({"AttributeID", "Unit", "Description"});
                } else if(dataType == SENSOR) {
                    queryBuilder.insert("Sensor").values({"SensorID", "Longitude", "Latitude", "Description"});
                } else {
                    queryBuilder.insert("Measurement").values({"Timestamp", "SensorID", "AttributeID", "Value"});
                }
            }

            if(dataType == ATTRIBUTE) {
                queryBuilder.bind(row.cells[0].as_str());
                queryBuilder.bind(row.cells[1].as_str());
                queryBuilder.bind(row.cells[2].as_str());
            } else if(dataType == SENSOR) {
                queryBuilder.bind(row.cells[0].as_str());
                queryBuilder.bind(row.cells[1].as_double());
                queryBuilder.bind(row.cells[2].as_double());
                queryBuilder.bind(row.cells[3].as_str());
            } else {
                queryBuilder.bind(row.cells[0].as_str());
                queryBuilder.bind(row.cells[1].as_str());
                queryBuilder.bind(row.cells[2].as_str());
                queryBuilder.bind(row.cells[3].as_double());
            }

            nbRows++;
        }

        queryBuilder.execute();
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