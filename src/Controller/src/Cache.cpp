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
    save();
}

Cache &Cache::operator=(Cache other) {
    swap(*this, other);
    return *this;
}

Cache::Cache(const Cache &other) {
    cache = other.cache;
}

Cache::Cache() {
    load();
}

Cache::~Cache() {

}

//TODO move that to utils ?
std::string replaceAll(std::string str, const std::string& from, const std::string& to) {
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
    }
    return str;
}

inline std::string to_string(const json &j)
{
    std::string result;
    if (j.type() == json::value_t::string) {
        result = j.get<std::string>();
    }
    else {
        result = j.dump();
    }

    return replaceAll(result, "\\\"", "\"");
}

void Cache::save() {
    std::ofstream stream(FILENAME);//, std::ios::out | std::ios::binary);
    try {
        std::unordered_map<std::string, std::string> s_cache;
        for (auto& [key, value] : cache) {
            s_cache[to_string(key)] = to_string(value);
        }
        json j(s_cache);

        std::vector<std::uint8_t> v_bson = json::to_ubjson(j);
        for (auto d : v_bson)
        {
            stream.write((char*)&d, sizeof(std::uint8_t));
        }

    } catch (const std::exception& e) { // caught by reference to base
        std::cout << " a standard exception was caught, with message '"
                  << e.what() << "'\n";
    }


    stream.close();
}

void Cache::load() {
    std::ifstream stream(FILENAME, std::ios::in | std::ios::binary);
    std::vector<uint8_t> contents((std::istreambuf_iterator<char>(stream)), std::istreambuf_iterator<char>());
    if (contents.size() > 0) {
        json j_from_bson = json::from_ubjson(contents);
        for (auto& [key, value] : j_from_bson.items()) {
            cache[json::parse(to_string(key))] = json::parse(to_string(value));
        }
    }
    stream.close();
}

void swap(Cache &first, Cache &second) {
    std::swap(first.cache, second.cache);
}
