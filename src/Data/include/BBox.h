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
        BBox(double left, double top, double right, double bottom);
        BBox(std::string stringValue);
        bool isNull();
        double getLeft() const;
        double getTop() const;
        double getRight() const;
        double getBottom() const;
        void setLeft(double d);
        void setTop(double d);
        void setRight(double d);
        void setBottom(double d);


        friend void to_json(json& j, const BBox& box);

        friend void from_json(const json& j, BBox& box);

    private:
        double left;   // min longitude    [-180, 180[
        double top;    // min latitude     [ -90,  90[
        double right;  // max longitude    [-180, 180[
        double bottom; // max latitude     [ -90,  90[
};




#endif //QUALITAIR_BBOX_H
