//
// Created by Wallyn Valentin on 17/02/2019.
//

#include "../include/ETL.h"
#include "../../Data/include/QueryBuilder.h"
#include <dirent.h>
#include <stdio.h>
#include <csvmonkey.hpp>

long ETL::ingest(std::string path) {
    long insertedRows = 0;
    for(std::string file : listCSVFiles(path)) {
        std::cout << file << std::endl;
        csvmonkey::MappedFileCursor cursor;
        cursor.open(file.c_str());

        csvmonkey::CsvReader reader(cursor, ';');
        csvmonkey::CsvCursor &row = reader.row();
        reader.read_row();

        int dataType = extractDataTypeFromFile(file);
        if(dataType == -1) {
            //TODO: error handling ?
            return -1;
        }

        int nbRows = 0;
        QueryBuilder queryBuilder;

        while(reader.read_row()) {
            if(nbRows == NB_ROW_PER_BATCH) {
                insertedRows += queryBuilder.executeUpdate();

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
            } else if(dataType == MEASURE){
                queryBuilder.bind(row.cells[0].as_str());
                queryBuilder.bind(row.cells[1].as_str());
                queryBuilder.bind(row.cells[2].as_str());
                queryBuilder.bind(row.cells[3].as_double());
            }

            nbRows++;
        }

        insertedRows += queryBuilder.executeUpdate();
    }

    return insertedRows;
}

std::vector<std::string> ETL::listCSVFiles(std::string path) {
    std::vector<std::string> files;
    DIR *dir;
    struct dirent *ent;

    if((dir = opendir(path.c_str())) != nullptr) {
        while((ent = readdir (dir)) != nullptr) {
            std::string fileName = ent->d_name;
            if(fileName.find(".csv") != std::string::npos) {
                files.push_back(path + "/" + fileName);
            }
        }
        closedir(dir);
    } else {
        //TODO: error handling ?
    }

    return files;
}

int ETL::extractDataTypeFromFile(std::string path) {
    int dataType = -1;
    std::ifstream fileStream(path);

    if(fileStream.good()) {
        std::string header;
        std::getline(fileStream, header);

        if(header == "AttributeID;Unit;Description;") dataType = ATTRIBUTE;
        else if(header == "SensorID;Latitude;Longitude;Description;") dataType = SENSOR;
        else if(header == "Timestamp;SensorID;AttributeID;Value;") dataType = MEASURE;
    }

    return dataType;
}

void ETL::getData() {

}