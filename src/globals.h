
#ifndef QUALITAIR_GLOBALS_H
#define QUALITAIR_GLOBALS_H

#include <vector>
#include <unordered_map>

typedef std::vector<std::vector<std::vector<std::unordered_map<std::string, double>>>> pointCollection;

typedef struct {
    double left;   // min longitude    [-180, 180[
    double top;    // min latitude     [ -90,  90[
    double right;  // max longitude    [-180, 180[
    double bottom; // max latitude     [ -90,  90[
} BBox;

#endif //QUALITAIR_GLOBALS_H
