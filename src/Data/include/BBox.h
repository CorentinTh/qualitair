//
// Created by basti on 04/03/2019.
//

#ifndef QUALITAIR_BBOX_H
#define QUALITAIR_BBOX_H

#include <string>
#include "nlohmann/json.hpp"
using json = nlohmann::json;

class BBox {
    public:
        BBox() : left(-1), top(-1), right(-1), bottom(-1) {};
        BBox(int left, int top, int right, int bottom);
        BBox(std::string stringValue);
        bool isNull();

        friend void to_json(json& j, const BBox& box);

        friend void from_json(const json& j, BBox& box);

    private:
        int left;   // min longitude    [-180, 180[
        int top;    // min latitude     [ -90,  90[
        int right;  // max longitude    [-180, 180[
        int bottom; // max latitude     [ -90,  90[


};




#endif //QUALITAIR_BBOX_H
