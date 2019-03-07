//
// Created by vwallyn on 03/03/19.
//

#ifndef QUALITAIR_UTILS_H
#define QUALITAIR_UTILS_H

struct pair_hash {
    template <class T>
    std::size_t operator () (const std::pair<Sensor,T> &p) const {
        auto h1 = std::hash<std::string>{}(p.first.getId());
        auto h2 = std::hash<T>{}(p.second);
        //simple
        return h1 ^ h2;
    }
};

#endif //QUALITAIR_UTILS_H
