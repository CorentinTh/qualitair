//
//        ----[  QUALIT'AIR  ]----
//
//    Marsaud Menseau Thomasset Wallyn
//  Copyright © 2019 - All right reserved
//

#include "../include/Octree.h"

namespace OT {

    Boundary::Boundary(double x0, double y0, double z0, double x1, double y1, double z1)
            : x0(x0), x1(x1), y0(y0), y1(y1), z0(z0), z1(z1) {

    }

    bool Boundary::contains(const point_t &point) const {
        return x0 <= point.x &&
               x1 >= point.x &&
               y0 <= point.y &&
               y1 >= point.y &&
               z0 <= point.z &&
               z1 >= point.z;
    }

    bool Boundary::intersects(const Boundary *b) const {
        return x0 <= b->x1 &&
               x1 >= b->x0 &&
               y0 <= b->y1 &&
               y1 >= b->y0 &&
               z0 <= b->z1 &&
               z1 >= b->z0;
    }

    double Boundary::getX0() const {
        return x0;
    }

    double Boundary::getY0() const {
        return y0;
    }

    double Boundary::getX1() const {
        return x1;
    }

    double Boundary::getY1() const {
        return y1;
    }

    double Boundary::getZ0() const {
        return z0;
    }

    double Boundary::getZ1() const {
        return z1;
    }

    Octree::Octree(Boundary *boundary, int maxCapacity, vector<point_t> *initNodes) : container(boundary),
                                                                                      maxCapacity(maxCapacity) {
        if (initNodes != nullptr) {
            for (auto node : *initNodes) {
                insert(node);
            }
        }

    }

    Octree::~Octree() {
        if (isDivided) {
            for (auto &node : nodes) {
                delete node;
            }
        }

        delete container;
    }

    bool Octree::insert(const point_t &point) {
        if (!container->contains(point)) {
            return false;
        }

        if (!isDivided) {
            if (capacity < maxCapacity) {
                ++capacity;
                points.emplace_back(point);

                return true;
            }

            divide();
        }

        for (auto &node : nodes) {
            if (node->insert(point)) return true;
        }

        return false;
    }

    void Octree::divide() {

        //          left    center   right
        //       top ┌────────┬────────┐
        //           │        │        │
        //           │   nw   │   ne   │
        //           │        │        │
        //    middle ├────────┼────────┤
        //           │        │        │
        //           │   sw   │   se   │
        //           │        │        │
        //    bottom └────────┴────────┘


        double x0 = container->getX0();
        double x1 = container->getX1();
        double y0 = container->getY0();
        double y1 = container->getY1();
        double z0 = container->getZ0();
        double z1 = container->getZ1();
        double dX = x0 + ((x1 - x0) / 2);
        double dY = y0 + ((y1 - y0) / 2);
        double dZ = z0 + ((z1 - z0) / 2);

        nodes[NWT] = new Octree(new Boundary(x0, y0, z0, dX, dY, dZ), maxCapacity, &points);
        nodes[NET] = new Octree(new Boundary(dX, y0, z0, x1, dY, dZ), maxCapacity, &points);
        nodes[SWT] = new Octree(new Boundary(x0, dY, z0, dX, y1, dZ), maxCapacity, &points);
        nodes[SET] = new Octree(new Boundary(dX, dY, z0, x1, y1, dZ), maxCapacity, &points);
        nodes[NWB] = new Octree(new Boundary(x0, y0, dZ, dX, dY, z1), maxCapacity, &points);
        nodes[NEB] = new Octree(new Boundary(dX, y0, dZ, x1, dY, z1), maxCapacity, &points);
        nodes[SWB] = new Octree(new Boundary(x0, dY, dZ, dX, y1, z1), maxCapacity, &points);
        nodes[SEB] = new Octree(new Boundary(dX, dY, dZ, x1, y1, z1), maxCapacity, &points);

//        nw = new Octree(new Boundary(x0,    y0,    dX, dY), maxCapacity, &points);
//        ne = new Octree(new Boundary(dX,  y0,    x1,  dY), maxCapacity, &points);
//        sw = new Octree(new Boundary(x0,    dY, dX, y1), maxCapacity, &points);
//        se = new Octree(new Boundary(dX,  dY, x1,  y1), maxCapacity, &points);

        isDivided = true;

        points.clear();
        capacity = 0;
    }

    vector<const point_t *> *Octree::query(Boundary *range) {
        auto points = new vector<const point_t *>();

        query(range, points);

        delete range;
        return points;
    }

    void Octree::query(Boundary *range, vector<const point_t *> *pointsRet) {
        if (!range->intersects(container)) {
            return;
        }

        if (isDivided) {

            for (auto &node : nodes) {
                node->query(range, pointsRet);
            }

        } else {
            for (auto const &point : points) {
                if (range->contains(point) &&
                    find(pointsRet->begin(), pointsRet->end(), &point) == pointsRet->end()) {
                    pointsRet->emplace_back(&point);
                }
            }
        }
    }
}





