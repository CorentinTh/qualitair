//
// Created by basti on 04/03/2019.
//

#ifndef QUALITAIR_BBOX_H
#define QUALITAIR_BBOX_H

#include <string>

class BBox {
    public:
        BBox() : left(0), top(0), right(0), bottom(0) {};
        BBox(int left, int top, int right, int bottom);
        BBox(std::string stringValue);
    private:
        int left;   // min longitude    [-180, 180[
        int top;    // min latitude     [ -90,  90[
        int right;  // max longitude    [-180, 180[
        int bottom; // max latitude     [ -90,  90[
};


#endif //QUALITAIR_BBOX_H
