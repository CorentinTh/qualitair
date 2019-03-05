//
// Created by Wallyn Valentin on 17/02/2019.
//

#include "../include/ETL.h"
#include "../../Data/include/QueryBuilder.h"
#include "../include/GeoFilter.h"
#include "../include/TimeFilter.h"
#include "../include/AttributeFilter.h"
#include "../include/SensorFilter.h"

void *ETL::getData(json config) {

    QueryBuilder qb;

    qb.select("*").from(config["type"]);

    if (config["hasBBox"]) {
        GeoFilter filter;

        filter.setBBox({config["BBox"]["left"], config["BBox"]["top"], config["BBox"]["right"], config["BBox"]["bottom"]});
        filter.applyTo(qb);
    }

    if (config["hasTimeRange"]) {
        TimeFilter filter;

        filter.setInterval(config["timeRange"]["start"], config["timeRange"]["end"]);
        filter.applyTo(qb);
    }

    if (config["hasAttributes"]) {
        AttributeFilter filter;

        filter.addAttributes(config["attributes"]);
        filter.applyTo(qb);
    }

    if (config["hasSensors"]) {
        SensorFilter filter;

        filter.addSensors(config["sensors"]);
        filter.applyTo(qb);
    }

    // TODO parse SQLite::Statement to vector
    // TODO manage interpolation
    return qb.execute();
}
