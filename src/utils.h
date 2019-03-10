//
// Created by vwallyn on 03/03/19.
//

#ifndef QUALITAIR_UTILS_H
#define QUALITAIR_UTILS_H

#include "Data/include/Sensor.h"
#include <ctime>
#include <sstream>
#include <iomanip>
#include <iostream>

struct pair_hash {
    template <class T>
    std::size_t operator () (const std::pair<Sensor,T> &p) const {
        auto h1 = std::hash<std::string>{}(p.first.getId());
        auto h2 = std::hash<T>{}(p.second);
        //simple
        return h1 ^ h2;
    }
};

static tm stringDateToTm(std::string stringDate, std::string pattern) {
    std::tm date = {};
    std::istringstream stringStream(stringDate);
    stringStream >> std::get_time(&date, pattern.c_str());

    if (!stringStream.fail()) {
        std::put_time(&date, "%c");
    }

    return date;
}

static time_t parseRFC3339Date(std::string stringDate) {
     if (stringDate == "") {
         return 0;
     }
    tm date = stringDateToTm(stringDate, "%Y-%m-%d %H:%M:%S");
    return mktime(&date) * 1000;
}

static time_t parseISO8601Date(std::string stringDate) {
    if (stringDate == "") {
         return 0;
     }
    unsigned long milisIndex = stringDate.find('.');
    int milis = std::stoi(stringDate.substr(milisIndex + 1, 3));
    tm date = stringDateToTm(stringDate.substr(0, milisIndex), "%Y-%m-%dT%H:%M:%S");

    return mktime(&date) * 1000 + milis;
}

#endif //QUALITAIR_UTILS_H
