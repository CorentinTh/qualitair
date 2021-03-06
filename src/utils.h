//
//        ----[  QUALIT'AIR  ]----
//
//    Marsaud Menseau Thomasset Wallyn
//  Copyright © 2019 - All right reserved
//

#ifndef QUALITAIR_UTILS_H
#define QUALITAIR_UTILS_H

#include "Data/include/Sensor.h"
#include <ctime>
#include <sstream>
#include <iomanip>
#include <iostream>

namespace utils {
    struct pair_hash {
        template<class T>
        std::size_t operator()(const std::pair<Sensor, T> &p) const {
            auto h1 = std::hash<std::string>{}(p.first.getId());
            auto h2 = std::hash<T>{}(p.second);
            //simple
            return h1 ^ h2;
        }
    };


    inline std::string replaceAll(std::string str, const std::string &from, const std::string &to) {
        size_t start_pos = 0;
        while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
            str.replace(start_pos, from.length(), to);
            start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
        }
        return str;
    }

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
        return mktime(&date);
    }

    static time_t parseISO8601Date(std::string stringDate) {
        if (stringDate == "") {
            return 0;
        }
        unsigned long milisIndex = stringDate.find('.');
        int milis = std::stoi(stringDate.substr(milisIndex + 1, 3));
        tm date = stringDateToTm(stringDate.substr(0, milisIndex), "%Y-%m-%dT%H:%M:%S");

        return mktime(&date);
    }

    static std::vector<std::string> unjoinString(std::string string) {
        std::vector<std::string> values;
        size_t position = 0;
        std::string value;

        while ((position = string.find(',')) != std::string::npos) {
            value = string.substr(0, position);
            values.push_back(value);
            string.erase(0, position + 1);
        }
        if (string != "") {
            values.push_back(string);
        }
        return values;
    }

    static std::string timestampToString(const time_t rawtime) {
        struct tm *dt;
        char buffer[30];
        dt = localtime(&rawtime);
        strftime(buffer, sizeof(buffer), "%d/%m/%Y %H:%M:%S", dt);
        return std::string(buffer);
    }
}


#endif //QUALITAIR_UTILS_H
