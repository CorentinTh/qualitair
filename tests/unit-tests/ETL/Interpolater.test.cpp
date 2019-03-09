#include "catch2/catch.hpp"

#include "../../../src/ETL/include/Interpolater.h"


bool pointCollectionEquals(pointCollection *a, pointCollection *b, double tolerance = 0.001) {
    if (a->size() != b->size() ||
        a->at(0).size() != b->at(0).size() ||
        a->at(0)[0].size() != b->at(0)[0].size()) {
        return false;
    }


    for (unsigned int i = 0; i < a->size(); ++i) {
        for (unsigned int j = 0; j < a->at(i).size(); ++j) {
            for (unsigned int k = 0; k < a->at(i)[j].size(); ++k) {
                for (auto &pairA : a->at(i)[j][k]) {
                    auto pairB = b->at(i)[j][k].find(pairA.first);

                    if (pairB != b->at(i)[j][k].end()) {
                        if (pairA.second - pairB->second > tolerance) {
                            return false;
                        }
                    } else {
                        return false;
                    }
                }
            }
        }
    }

    return true;
}

TEST_CASE("Interpolation 1x3x3 with 1 attribute", "[]") {
    Interpolater interpolater;

    vector<Measurement *> input = {
            new Measurement(0, Sensor("1", 0, 0, ""), Attribute("1", "", ""), 5),
            new Measurement(0, Sensor("1", 20, 20, ""), Attribute("1", "", ""), 10),
    };

    json config = {
            {"spatialGranularity",   10},
            {"temporalGranularity",  10},
            {"BBox",                 {
                                             {"left",      0},
                                             {"right",    20},
                                             {"top",  20},
                                             {"bottom", 0}
                                     }},
            {"start",                0},
            {"end",                  0},
            {"minimalInterDistance", {
                                             {"longitude", 5000},
                                             {"latitude", 5000},
                                             {"time", 50}
                                     }}
    };

    pointCollection output = {{
                                      {{{"1", 5.000}}, {{"1", 5.833}}, {{"1", 7.500}}},
                                      {{{"1", 5.833}}, {{"1", 7.500}}, {{"1", 9.167}}},
                                      {{{"1", 7.500}}, {{"1", 9.167}}, {{"1", 10.00}}}
                              }};

    auto result = interpolater.interpolate(input, config);

    CHECK(pointCollectionEquals(result, &output));
}


TEST_CASE("Interpolation 1x3x3 with 2 attributes", "[]") {
    Interpolater interpolater;

    vector<Measurement *> input = {
            new Measurement(0, Sensor("1", 0, 0, ""), Attribute("1", "", ""), 5),
            new Measurement(0, Sensor("1", 20, 20, ""), Attribute("1", "", ""), 10),
    };


    json config = {
            {"spatialGranularity",   10},
            {"temporalGranularity",  10},
            {"BBox",                 {
                                             {"left",      0},
                                             {"right",    20},
                                             {"top",  20},
                                             {"bottom", 0}
                                     }},
            {"start",                0},
            {"end",                  0},
            {"minimalInterDistance", {
                                             {"longitude", 5000},
                                             {"latitude", 5000},
                                             {"time", 50}
                                     }}
    };

    pointCollection output = {{
                                      {{{"1", 5.000}, {"2", 5.000}}, {{"1", 5.833}, {"2", 5.833}}, {{"1", 7.500}, {"2", 7.500}}},
                                      {{{"1", 5.833}, {"2", 5.833}}, {{"1", 7.500}, {"2", 7.500}}, {{"1", 9.167}, {"2", 9.167}}},
                                      {{{"1", 7.500}, {"2", 7.500}}, {{"1", 9.167}, {"2", 9.167}}, {{"1", 10.00}, {"2", 10.00}}}
                              }};

    auto result = interpolater.interpolate(input, config);

    CHECK(pointCollectionEquals(result, &output));
}

TEST_CASE("Interpolation 3x3x3 with 2 attributes", "[]") {
    Interpolater interpolater;

    vector<Measurement *> input = {
            new Measurement(0, Sensor("1", 0, 0, ""), Attribute("1", "", ""), 5),
            new Measurement(0, Sensor("1", 20, 20, ""), Attribute("1", "", ""), 10),
            new Measurement(0, Sensor("1", 0, 0, ""), Attribute("2", "", ""), 5),
            new Measurement(0, Sensor("1", 20, 20, ""), Attribute("2", "", ""), 10),
            new Measurement(20, Sensor("1", 0, 0, ""), Attribute("1", "", ""), 10),
            new Measurement(20, Sensor("1", 20, 20, ""), Attribute("1", "", ""), 5),
            new Measurement(20, Sensor("1", 0, 0, ""), Attribute("2", "", ""), 10),
            new Measurement(20, Sensor("1", 20, 20, ""), Attribute("2", "", ""), 5),
    };

    json config = {
            {"spatialGranularity",   10},
            {"temporalGranularity",  10},
            {"BBox",                 {
                                             {"left",      0},
                                             {"right",    20},
                                             {"top",  20},
                                             {"bottom", 0}
                                     }},
            {"start",                0},
            {"end",                  20},
            {"minimalInterDistance", {
                                             {"longitude", 5000},
                                             {"latitude", 5000},
                                             {"time", 50}
                                     }}
    };

    pointCollection output = {
            {
                    {{{"1", 5.000},  {"2", 5.000},},  {{"1", 6.324}, {"2", 6.324},}, {{"1", 7.500}, {"2", 7.500}}},
                    {{{"1", 6.324}, {"2", 6.324},}, {{"1", 7.500}, {"2", 7.500},}, {{"1", 8.676}, {"2", 8.676}}},
                    {{{"1", 7.500}, {"2", 7.500},}, {{"1", 8.676}, {"2", 8.676},}, {{"1", 10.000}, {"2", 10.000}}},
            },
            {
                    {{{"1", 7.500},  {"2", 7.500},},  {{"1", 7.500}, {"2", 7.500},}, {{"1", 7.500}, {"2", 7.500}}},
                    {{{"1", 7.500}, {"2", 7.500},}, {{"1", 7.500}, {"2", 7.500},}, {{"1", 7.500}, {"2", 7.500}}},
                    {{{"1", 7.500}, {"2", 7.500},}, {{"1", 7.500}, {"2", 7.500},}, {{"1", 7.500},  {"2", 7.500}}},
            },
            {
                    {{{"1", 10.000}, {"2", 10.000},}, {{"1", 8.676}, {"2", 8.676},}, {{"1", 7.500}, {"2", 7.500}}},
                    {{{"1", 8.676}, {"2", 8.676},}, {{"1", 7.500}, {"2", 7.500},}, {{"1", 6.324}, {"2", 6.324}}},
                    {{{"1", 7.500}, {"2", 7.500},}, {{"1", 6.324}, {"2", 6.324},}, {{"1", 5.000},  {"2", 5.000}}},
            },
    };

    auto result = interpolater.interpolate(input, config);

    CHECK(pointCollectionEquals(result, &output));
}


