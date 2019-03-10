//
// Created by vwallyn on 03/03/19.
//

#ifndef QUALITAIR_UTILS_H
#define QUALITAIR_UTILS_H

#include "Data/include/Sensor.h"

namespace utils
{
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
}

#endif //QUALITAIR_UTILS_H
