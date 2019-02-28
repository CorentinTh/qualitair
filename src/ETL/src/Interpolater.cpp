//
// Created by Wallyn Valentin on 17/02/2019.
//

#include "../include/Interpolater.h"
#include "../include/Octree.h"


pointCollection Interpolater::interpolate(const vector<Measurement> &measures, const json &config) {

    auto trees = new unordered_map<string, OT::Octree *>;

    int minLon = -180;
    int minLat = -90;
    int maxLon = -90;
    int maxLat = -90;
    int minT = 0;
    int maxT = 1000000;
    // Prepare data
    for (const auto &measure : measures) {
        auto it = trees->find(measure.getAttribute().getId());
        if (it == trees->end()) {
            trees->insert(make_pair(
                    measure.getAttribute().getId(),
                    new OT::Octree(new OT::Boundary(minLon, minLat, minT, maxLon, maxLat, maxT))
            ));
        } else {
            it->second->insert({
                measure.getSensor().getLongitude(),
                measure.getSensor().getLatitude(),
                1.
            });
        }
    }

//    auto * qt = new Quadtre();
    // get minLon
    // get minLat
    // get maxLon
    // get maxLat

    // Add each point in quadtree
    // for(x from 0 to

    return {{{{{"type", 1}}}}};
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

