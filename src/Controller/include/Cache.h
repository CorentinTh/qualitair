//
//        ----[  QUALIT'AIR  ]----
//
//    Marsaud Menseau Thomasset Wallyn
//  Copyright © 2019 - All right reserved
//

#ifndef QUALITAIR_CACHE_H
#define QUALITAIR_CACHE_H

#include <nlohmann/json.hpp>

using json = nlohmann::json;

class Cache {
public:
    json *get(json request);

    void put(json request, json result);

    Cache &operator=(Cache other);

    Cache(const Cache &other);

    Cache();

    virtual ~Cache();

protected:
    friend void swap(Cache &first, Cache &second);

    void save();

    void load();

    std::unordered_map<json, json> cache;
};

#endif //QUALITAIR_CACHE_H
