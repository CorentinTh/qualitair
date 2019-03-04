//
// Created by basti on 04/03/2019.
//

#include "../include/BBox.h"

BBox::BBox(int left, int top, int right, int bottom) {
    this->left = left;
    this->top = top;
    this->right = right;
    this->bottom =  bottom;
}

BBox::BBox(std::string stringValue) {
    int values[4] = {0};
    size_t position = 0;
    std::string value;

    for(int i = 0; (position = stringValue.find(',')) != std::string::npos && i < 3; i++) {
        value = stringValue.substr(0, position);
        values[i] = std::stoi(value);
        stringValue.erase(0, position + 1);
    }

    left = values[0];
    top = values[1];
    right = values[2];
    bottom = values[3];
}

bool BBox::isNull() {
    return left == -1 && top == -1 && right == -1 && bottom == -1;
}