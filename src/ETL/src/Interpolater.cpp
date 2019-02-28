//
// Created by Wallyn Valentin on 17/02/2019.
//

#include "../include/Interpolater.h"
#include "../include/Octree.h"


typedef struct {
    int start;
    int end;
} TimeRange;

pointCollection *Interpolater::interpolate(const vector<Measurement> &measures, const json &config) {

    auto trees = new unordered_map<string, OT::Octree *>;

//    int minLon = -180;  // Narrow with config
//    int minLat = -90;   // Narrow with config
//    int maxLon = -90;   // Narrow with config
//    int maxLat = -90;   // Narrow with config

    BBox area = {0, 0, 50, 50};     // config["bbox"]
    TimeRange timeRange = {1550000000, 1660158000}; // {config["timerange"]["start"], config["timerange"]["end"]}

    int x0 = area.left;
    int x1 = area.right;
    int y0 = area.top;
    int y1 = area.bottom;
    int z0 = timeRange.start;
    int z1 = timeRange.end;
    int xFactor = 10;  // config["spatialGranularity"];
    int yFactor = 10;  // config["spatialGranularity"];
    int zFactor = 1000000;  // config["temporalGranularity"];

    double interRadiusX = 5;
    double interRadiusY = 5;
    double interRadiusZ = 5;

    // Preparing the data.
    // We insert each measure in an octree according to the attributeID
    for (const auto &measure : measures) {
        auto it = trees->find(measure.getAttribute().getId());
        if (it == trees->end()) {
            trees->insert(make_pair(
                    measure.getAttribute().getId(),
                    new OT::Octree(new OT::Boundary(x0, y0, z0, x1, y1, z1))
            ));
        } else {

            OT::point_t p ={
                                  measure.getSensor().getLongitude(),
                                  measure.getSensor().getLongitude(),
                                  (double) measure.getTimestamp(),
                                  (void*) &measure.getValue()
                          };

            it->second->insert(
                    {
                            measure.getSensor().getLongitude(),
                            measure.getSensor().getLatitude(),
                            (double) measure.getTimestamp(),
                            (void *) &measure
                    }
            );
        }
    }


    unsigned long xCount = (unsigned long) (x1 - x0) / xFactor;
    unsigned long yCount = (unsigned long) (y1 - y0) / yFactor;
    unsigned long zCount = (unsigned long) (z1 - z0) / zFactor;

    auto *collection = new pointCollection(zCount);

    // Time
    for (unsigned long z = 0; z < zCount; ++z) {
        double zReal = z0 + zCount * zFactor;

        collection->at(z).resize(yCount);

        // Latitude
        for (unsigned long y = 0; y < yCount; ++y) {
            double yReal = y0 + yCount * yFactor;

            collection->at(z)[y].resize(xCount);

            // Longitude
            for (unsigned long x = 0; x < xCount; ++x) {
                double xReal = x0 + xCount * xFactor;

                cout << x << " " << y << " " << z << endl;

                auto attributes = &collection->at(z)[y][x];

                for (auto &pair: *trees) {
                    auto neigboors = pair.second->query(new OT::Boundary(
                            xReal - interRadiusX,
                            yReal - interRadiusY,
                            zReal - interRadiusZ,
                            xReal + interRadiusX,
                            yReal + interRadiusY,
                            zReal + interRadiusZ
                    ));

                    attributes->insert(make_pair(pair.first, interpolate(xReal, yReal, zReal, neigboors)));

                }


            }
        }
    }





//    auto * qt = new Quadtre();
    // get minLon
    // get minLat
    // get maxLon
    // get maxLat

    // Add each point in quadtree
    // for(x from 0 to

//    return {{{{{"type", 1}}}}};
}

Interpolater &Interpolater::operator=(Interpolater other) {
    return *this;
}

Interpolater::Interpolater(const Interpolater &other) {

}

Interpolater::Interpolater() {

}

Interpolater::~Interpolater() {

}

double Interpolater::interpolate(double x, double y, double z, vector<Measurement *> *neigboors) {

    double value = 0;

    for (auto &measurement : *neigboors) {
        double distance = (x)
    }


    return 0;
}

