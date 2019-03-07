//
// Created by Wallyn Valentin on 17/02/2019.
//

#include "../include/Interpolater.h"
#include <unordered_map>


pointCollection *Interpolater::interpolate(const vector<Measurement *> &measures, const json &config) {

    auto trees = new unordered_map<string, OT::Octree *>;

    double x0 = config["BBox"]["left"];
    double x1 = config["BBox"]["right"];
    double y0 = config["BBox"]["bottom"];
    double y1 = config["BBox"]["top"];
    double z0 = config["start"];
    double z1 = config["end"];
    double xFactor = config["spatialGranularity"];
    double yFactor = config["spatialGranularity"];
    double zFactor = config["temporalGranularity"];

    double interRadiusX = config["minimalInterDistance"]["longitude"];
    double interRadiusY = config["minimalInterDistance"]["latitude"];
    double interRadiusZ = config["minimalInterDistance"]["time"];

    // Preparing the data.
    // We insert each measure in an octree according to the attributeID
    for (const auto &measure : measures) {
        auto it = trees->find(measure->getAttribute().getId());
        if (it == trees->end()) {
            trees->insert(make_pair(
                    measure->getAttribute().getId(),
                    new OT::Octree(new OT::Boundary(x0, y0, z0, x1, y1, z1))
            ));
            it = trees->find(measure->getAttribute().getId());
        }

        OT::point_t p = {
                measure->getSensor().getLongitude(),
                measure->getSensor().getLongitude(),
                (double) measure->getTimestamp(),
                new double(measure->getValue())
        };

        it->second->insert(p);

    }

    unsigned long xCount =(unsigned long) 1 + (unsigned long) ((x1 - x0) / xFactor);
    unsigned long yCount =(unsigned long) 1 + (unsigned long) ((y1 - y0) / yFactor);
    unsigned long zCount =(unsigned long) 1 + (unsigned long) ((z1 - z0) / zFactor);

    auto *collection = new pointCollection(zCount);

    // Time
    for (unsigned long z = 0; z < zCount; ++z) {
        double zReal = z0 + z * zFactor;

        collection->at(z).resize(yCount);

        // Latitude
        for (unsigned long y = 0; y < yCount; ++y) {
            double yReal = y0 + y * yFactor;

            collection->at(z)[y].resize(xCount);

            // Longitude
            for (unsigned long x = 0; x < xCount; ++x) {
                double xReal = x0 + x * xFactor;

                unordered_map<string, double> attributes;

                for (auto &pair: *trees) {
                    auto neigboors = pair.second->query(new OT::Boundary(
                            xReal - interRadiusX,
                            yReal - interRadiusY,
                            zReal - interRadiusZ,
                            xReal + interRadiusX,
                            yReal + interRadiusY,
                            zReal + interRadiusZ
                    ));

                    auto d = interpolate(xReal, yReal, zReal, neigboors);
                    attributes.insert(make_pair(pair.first, d));
                }

                collection->at(z)[y][x] = attributes;

            }
        }
    }

    for (auto &tree : *trees) {
        delete tree.second;
    }
    delete trees;

    return collection;
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

double Interpolater::interpolate(double x, double y, double z, vector<const OT::point_t *> *neigboors) {

    double distance = 0;
    double value = 0;
    double collector = 0;
    double weight = 0;
    double result = 0;

    for (auto &m : *neigboors) {
        distance = euclideanSquared(x, y, z, m->x, m->y, m->z);
        value = *(double *) m->data;

        if(distance < 0.0001) return value;

        weight = 1.0/distance;
        collector += weight;
        result += weight * value;
    }

    return result /collector;
}

/**
 * 3D distance squared
 * @param {double} x0 - Start point x coordinate
 * @param {double} y0 - Start point y coordinate
 * @param {double} z0 - Start point z coordinate
 * @param {double} x1 - End point x coordinate
 * @param {double} y1 - End point y coordinate
 * @param {double} z1 - End point z coordinate
 * @return {double}
 */
double euclideanSquared(double x0, double y0, double z0, double x1, double y1, double z1) {
    return (x0 - x1) * (x0 - x1) + (y0 - y1) * (y0 - y1) + (z0 - z1) * (z0 - z1);
};
