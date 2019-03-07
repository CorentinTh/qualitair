//
// Created by Wallyn Valentin on 17/02/2019.
//

#include "../include/ETL.h"
#include "../../Data/include/QueryBuilder.h"
#include "../include/Interpolater.h"


#include <iostream>
#include <SQLiteCpp/Column.h>

using namespace std;

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
            cerr << "Wrong type" << endl;
        }

    } catch (json::out_of_range &e) {
        cerr << "Attribute 'type' must be specified in ETL::getData config";
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

    try {
        auto statement = qb->execute();

        if (config["type"] == ETL::MEASURE) {

            while (statement->executeStep()) {
                result->emplace_back(new Measurement(
                        statement->getColumn("timestamp"),
                        {
                                statement->getColumn("sensorId"),
                                statement->getColumn("latitude"),
                                statement->getColumn("longitude"),
                                statement->getColumn("sensorDescription")
                        }, {
                                statement->getColumn("attributeId"),
                                statement->getColumn("unit"),
                                statement->getColumn("attributeDescription")
                        },
                        statement->getColumn("value")
                ));
            }

        } else if (config["type"] == ETL::SENSOR) {

            while (statement->executeStep()) {
                result->emplace_back(new Sensor(
                        statement->getColumn("sensorId"),
                        statement->getColumn("latitude"),
                        statement->getColumn("longitude"),
                        statement->getColumn("description")
                ));
            }

        } else if (config["type"] == ETL::ATTRIBUTE) {

            while (statement->executeStep()) {
                result->emplace_back(new Attribute(
                        statement->getColumn("attributeId"),
                        statement->getColumn("unit"),
                        statement->getColumn("description")
                ));
            }

        }

    } catch (SQLite::Exception &e) {
        cerr << "An unexpected error occurred while fetching from the database. Please retry." << endl;
        cerr << e.what() << endl;
    }


    return result;
}

void ETL::setMeasurementConfig(QueryBuilder *qb) {
    qb->select("Sensor.sensorId as sensorId");
    qb->select("Attribute.attributeId as attributeId");
    qb->select("timestamp");
    qb->select("value");
    qb->select("longitude");
    qb->select("latitude");
    qb->select("unit");
    qb->select("Sensor.description as sensorDescription");
    qb->select("Attribute.description as attributeDescription");
    qb->from("Measurement");
    qb->join("Sensor");
    qb->join("Attribute");
    qb->where("Measurement.attributeId = Attribute.attributeId");
    qb->where("Measurement.sensorId = Sensor.sensorId");
}


void ETL::setSensorConfig(QueryBuilder *qb) {
    qb->select("*");
    qb->from("Sensor");
}

void ETL::setAttributeConfig(QueryBuilder *qb) {
    qb->select("*");
    qb->from("Attribute");
}
