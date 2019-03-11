//
// Created by basti on 04/03/2019.
//

#include "../include/BBox.h"

BBox::BBox(double l, double t, double r, double b) : left(l), top(t), right(r), bottom(b) {

}

BBox::BBox(std::string stringValue) {
    if (stringValue == "") {
        left = -1;
        bottom = -1;
        right = -1;
        top = -1;
        return;
    }

    double values[4] = {0};
    size_t position = 0;
    std::string value;

    for(int i = 0; (position = stringValue.find(',')) != std::string::npos || i < 4; i++) {
        value = stringValue.substr(0, position);
        values[i] = std::stod(value);
        stringValue.erase(0, position + 1);
    }

    /*left = values[0];
    top = values[1];
    right = values[2];
    bottom = values[3];*/
    left = values[0];
    bottom = values[1];
    right = values[2];
    top = values[3];
}

bool BBox::isNull() {
    return left == -1 && top == -1 && right == -1 && bottom == -1;
}

double BBox::getLeft() const{
    return this->left;
}
double BBox::getTop() const{
    return this->top;
}
double BBox::getRight() const{
    return this->right;
}
double BBox::getBottom() const{
    return this->bottom;
}
void BBox::setLeft(double d){
    this->left = d;
}
void BBox::setTop(double d){
    this->top = d;
}
void BBox::setRight(double d){
    this->right = d;
}
void BBox::setBottom(double d){
    this->bottom = d;
}

void to_json(json& j, const BBox& box) {
    j = json{
            {"left", box.left},
            {"top", box.top},
            {"right", box.right},
            {"bottom", box.bottom}
    };
}

void from_json(const json& j, BBox& box) {
    j.at("left").get_to(box.left);
    j.at("top").get_to(box.top);
    j.at("right").get_to(box.right);
    j.at("bottom").get_to(box.bottom);
}