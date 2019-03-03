
#ifndef QUALITAIR_GLOBALS_H
#define QUALITAIR_GLOBALS_H

#include <vector>
#include <unordered_map>

typedef std::vector<std::vector<std::vector<std::unordered_map<std::string, double>>>> pointCollection;

typedef struct {
    int left;   // min longitude    [-180, 180[
    int top;    // min latitude     [ -90,  90[
    int right;  // max longitude    [-180, 180[
    int bottom; // max latitude     [ -90,  90[
} BBox;

#endif //QUALITAIR_GLOBALS_H
