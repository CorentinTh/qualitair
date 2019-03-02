//
// Created by vwallyn on 02/03/19.
//

#include <fstream>
#include "../include/Cache.h"
#include <iostream>

const std::string FILENAME = "/tmp/.qualitair_cache";

json* Cache::get(json request) {
    //TODO better lookup to find also partial match
    return new json(cache[request]);
}

void Cache::put(json request, json result) {
    cache[request] = result;
    //save();
}

Cache &Cache::operator=(Cache other) {
    swap(*this, other);
    return *this;
}

Cache::Cache(const Cache &other) {
    cache = other.cache;
}

Cache::Cache() {
    //load();
}

Cache::~Cache() {

}

inline std::string to_string(const json &j)
{
    if (j.type() == json::value_t::string) {
        return j.get<std::string>();
    }

    return j.dump();
}

void Cache::save() {
    std::ofstream stream(FILENAME);//, std::ios::out | std::ios::binary);
    try {
        std::unordered_map<std::string, std::string> s_cache;
        for (auto& [key, value] : cache) {
            s_cache[to_string(key)] = to_string(value);
        }
        /*for (auto& [key, value] : s_cache) {
            std::cout << key << std::endl;
            std::cout << value << std::endl;
        }*/
        json j(s_cache);

        /*std::vector<std::uint8_t> v_bson = json::to_ubjson(j);
        for (auto d : v_bson)
        {
            stream.write((char*)&d, sizeof(std::uint8_t));
        }*/

        j >> stream;
    } catch (const std::exception& e) { // caught by reference to base
        std::cout << " a standard exception was caught, with message '"
                  << e.what() << "'\n";
    }


    stream.close();
}

void Cache::load() {

    std::ifstream stream(FILENAME); //, std::ios::in | std::ios::binary);

    if (stream.good())
    {
        json j;
        stream >> j;

        for (auto& [key, value] : j.items()) {
            std::cout << key << std::endl;
            std::cout << value << std::endl;

            //cache[key] = value;
        }
    }


    /*std::vector<uint8_t> contents((std::istreambuf_iterator<char>(stream)), std::istreambuf_iterator<char>());
    std::cout << "file size: " << contents.size() << std::endl;
    if (contents.size() > 0) {

        json j_from_bson = json::from_ubjson(contents);
        std::cout <<  j_from_bson << std::endl;
        for (auto& [key, value] : j_from_bson.items()) {
            std::cout << key << std::endl;
            std::cout << value.dump() << std::endl;

            cache[key] = json::parse("{}");
        }
    }*/

    stream.close();


}

void swap(Cache &first, Cache &second) {
    std::swap(first.cache, second.cache);
}
