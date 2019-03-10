//
// Created by Wallyn Valentin on 17/02/2019.
//

#include "../include/ETL.h"
#include "../../Data/include/QueryBuilder.h"
#include "../include/Interpolater.h"
#include "SQLiteCpp/Column.h"
#include "../../utils.h"

#include <dirent.h>
#include <stdio.h>
#include <csvmonkey.hpp>
#include "easylogging++.h"
#include "../../Data/include/ConnectionFactory.h"

long ETL::ingest(std::string path) {
    long insertedRows = 0;

    dropDatabaseIndexs();
    for(std::string file : listCSVFiles(path)) {
        csvmonkey::MappedFileCursor cursor;
        cursor.open(file.c_str());

        csvmonkey::CsvReader reader(cursor, ';');
        csvmonkey::CsvCursor &row = reader.row();
        reader.read_row();

        int dataType = extractDataTypeFromFile(file);
        if(dataType == -1) {
            //TODO: error handling ?
            createDatabaseIndexs();
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
                queryBuilder.bind(parseISO8601Date(row.cells[0].as_str()));
                queryBuilder.bind(row.cells[1].as_str());
                queryBuilder.bind(row.cells[2].as_str());
                queryBuilder.bind(row.cells[3].as_double());
            }

            nbRows++;
        }

        insertedRows += queryBuilder.executeUpdate();
    }

    createDatabaseIndexs();
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



void *ETL::getData(json config) {

    QueryBuilder qb;

    try {
        if (config.at("type") == ETL::MEASURE) {
            setMeasurementConfig(&qb);
        }else if (config.at("type")  == ETL::SENSOR) {
            setSensorConfig(&qb);
        }else if (config.at("type")  == ETL::ATTRIBUTE) {
            setAttributeConfig(&qb);
        }else{
            LOG(ERROR) << "Wrong type" ;
        }

    } catch (json::out_of_range &e) {
        LOG(ERROR) << "Attribute 'type' must be specified in ETL::getData config";
    }

    setFilters(&qb, config);

    void *data = extractData(&qb, config);
    try {
        if(config.at("doInterpolation") && config.at("type") == ETL::MEASURE){
            Interpolater interpolater;
            data = interpolater.interpolate(*(vector< Measurement*>*) data, config);
        }
    } catch (json::out_of_range &e) {}

    return data;
}

void ETL::setFilters(QueryBuilder *qb, json config) {

    try {
        if (config.at("hasBBox")) {
            GeoFilter filter;

            filter.setBBox(
                    {config["BBox"]["left"], config["BBox"]["top"], config["BBox"]["right"], config["BBox"]["bottom"]});
            filter.applyTo(*qb);
        }
    } catch (json::out_of_range &e) {}

    try {
        if (config.at("hasStart")) {
            TimeFilter filter;

            filter.setStart(config["start"]);
            filter.applyTo(*qb);
        }
    } catch (json::out_of_range &e) {}

    try {
        if (config.at("hasEnd")) {
            TimeFilter filter;

            filter.setEnd(config["end"]);
            filter.applyTo(*qb);
        }
    } catch (json::out_of_range &e) {}

    try {
        if (config.at("hasAttributes")) {
            AttributeFilter filter;

            filter.addAttributes(config["attributes"]);
            filter.applyTo(*qb);
        }
    } catch (json::out_of_range &e) {}

    try {
        if (config.at("hasSensors")) {
            SensorFilter filter;

            filter.addSensors(config["sensors"]);
            filter.applyTo(*qb);
        }
    } catch (json::out_of_range &e) {}

}

void *ETL::extractData(QueryBuilder *qb, json config) {

    auto result = new vector<void *>;

    SQLite::Statement * statement;
    try {
        statement = qb->execute();


        try {

            if (config["type"] == ETL::MEASURE) {

                while (statement->executeStep()) {
                    result->emplace_back(new Measurement(
                            statement->getColumn("Timestamp"),
                            {
                                    statement->getColumn("SensorID"),
                                    statement->getColumn("Latitude"),
                                    statement->getColumn("Longitude"),
                                    statement->getColumn("SensorDescription")
                            }, {
                                    statement->getColumn("AttributeID"),
                                    statement->getColumn("Unit"),
                                    statement->getColumn("AttributeDescription")
                            },
                            statement->getColumn("Value")
                    ));
                }

            } else if (config["type"] == ETL::SENSOR) {

                while (statement->executeStep()) {
                    result->emplace_back(new Sensor(
                            statement->getColumn("SensorID"),
                            statement->getColumn("Latitude"),
                            statement->getColumn("Longitude"),
                            statement->getColumn("Description")
                    ));
                }

            } else if (config["type"] == ETL::ATTRIBUTE) {

                while (statement->executeStep()) {
                    result->emplace_back(new Attribute(
                            statement->getColumn("AttributeID"),
                            statement->getColumn("Unit"),
                            statement->getColumn("Description")
                    ));
                }

            }

        } catch (SQLite::Exception &e) {
            LOG(ERROR) << "An unexpected error occurred while fetching from the database. Please retry.";
            LOG(ERROR) << e.what();
        }
    }catch (SQLite::Exception &e){
        LOG(ERROR) << "Error while executing the SQL request.";
        LOG(ERROR) << e.what();
    }






    return result;
}

void ETL::setMeasurementConfig(QueryBuilder *qb) {
    qb->select("Sensor.SensorID as SensorID");
    qb->select("Attribute.AttributeID as AttributeID");
    qb->select("Timestamp");
    qb->select("Value");
    qb->select("Longitude");
    qb->select("Latitude");
    qb->select("Unit");
    qb->select("Sensor.Description as SensorDescription");
    qb->select("Attribute.Description as AttributeDescription");
    qb->from("Measurement");
    qb->join("Sensor");
    qb->join("Attribute");
    qb->where("Measurement.AttributeID = Attribute.AttributeID");
    qb->where("Measurement.SensorID = Sensor.SensorID");
    qb->orderBy("Timestamp");
}


void ETL::setSensorConfig(QueryBuilder *qb) {
    qb->select("*");
    qb->from("Sensor");
}

void ETL::setAttributeConfig(QueryBuilder *qb) {
    qb->select("*");
    qb->from("Attribute");
}

void ETL::createDatabaseIndexs() {
    SQLite::Database * database = ConnectionFactory::getConnection();
    database->exec(
            "CREATE INDEX index_Attribute_AttributeID ON Attribute ( AttributeID ASC );"
            "CREATE INDEX index_Measurement_AttributeID ON Measurement ( AttributeID ASC );"
            "CREATE INDEX index_Measurement_SensorID ON Measurement ( SensorID ASC );"
            "CREATE INDEX index_Measurement_Timestamp ON Measurement ( Timestamp ASC );"
            "CREATE INDEX index_Sensor_Latitude ON Sensor ( Latitude ASC );"
            "CREATE INDEX index_Sensor_Longitude ON Sensor ( Longitude ASC );"
            "CREATE INDEX index_Sensor_SensorID ON Sensor ( SensorID ASC );"
    );
}

void ETL::dropDatabaseIndexs() {
    SQLite::Database * database = ConnectionFactory::getConnection();
    database->exec(
            "DROP INDEX index_Attribute_AttributeID;"
            "DROP INDEX index_Measurement_AttributeID;"
            "DROP INDEX index_Measurement_SensorID;"
            "DROP INDEX index_Measurement_Timestamp;"
            "DROP INDEX index_Sensor_Latitude;"
            "DROP INDEX index_Sensor_Longitude;"
            "DROP INDEX index_Sensor_SensorID;"
    );
}
