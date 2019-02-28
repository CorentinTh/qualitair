//
// Created by cthomasset on 27/02/19.
//

#include "../include/Quadtree.h"

namespace QT {

    Boundary::Boundary(int x0, int y0, int x1, int y1) : x0(x0), x1(x1), y0(y0), y1(y1) {

    }

    bool Boundary::contains(const point_t &point) const {
        return x0 <= point.x &&
               x1 >= point.x &&
               y0 <= point.y &&
               y1 >= point.y;
    }

    bool Boundary::intersects(const Boundary *b) const {
        return x0 <= b->x1 &&
               x1 >= b->x0 &&
               y0 <= b->y1 &&
               y1 >= b->y0;
    }

    int Boundary::getX0() const {
        return x0;
    }

    int Boundary::getY0() const {
        return y0;
    }

    int Boundary::getX1() const {
        return x1;
    }

    int Boundary::getY1() const {
        return y1;
    }

    Quadtree::Quadtree(Boundary *boundary, int maxCapacity, vector<point_t> *initNodes) : container(boundary), maxCapacity(maxCapacity) {
        if(initNodes != nullptr){
            for(auto node : *initNodes){
                insert(node);
            }
        }

    }

    Quadtree::~Quadtree() {
        delete ne;
        delete nw;
        delete se;
        delete sw;

        delete container;
    }

    bool Quadtree::insert(const point_t &node) {
        if (!container->contains(node)) {
            return false;
        }

        if (!isDivided) {
            if(capacity < maxCapacity){
                ++capacity;
                points.emplace_back(node);

                return true;
            }

            divide();
        }

        if (nw->insert(node)) return true;
        if (ne->insert(node)) return true;
        if (sw->insert(node)) return true;
        if (se->insert(node)) return true;

        return false;
    }

    void Quadtree::divide() {

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


        int left = container->getX0();
        int right = container->getX1();
        int top = container->getY0();
        int bottom = container->getY1();
        int center = left + ((right - left) / 2);
        int middle = top + ((bottom - top) / 2);

        nw = new Quadtree(new Boundary(left,    top,    center, middle), maxCapacity, &points);
        ne = new Quadtree(new Boundary(center,  top,    right,  middle), maxCapacity, &points);
        sw = new Quadtree(new Boundary(left,    middle, center, bottom), maxCapacity, &points);
        se = new Quadtree(new Boundary(center,  middle, right,  bottom), maxCapacity, &points);

        isDivided = true;

        points.clear();
        capacity = 0;
    }

    vector<void *>* Quadtree::query(Boundary *range) {
        auto points = new vector<void *> ();

        query(range, points);

        delete range;
        return points;
    }

    void Quadtree::query(Boundary *range, vector<void *> *pointsRet) {
        if(!range->intersects(container)){
            return;
        }

        if(isDivided){
            nw->query(range, pointsRet);
            ne->query(range, pointsRet);
            sw->query(range, pointsRet);
            se->query(range, pointsRet);
        }else{
            for (auto const& point : points) {
                if(range->contains(point) && find(pointsRet->begin(), pointsRet->end(), point.data) == pointsRet->end()){
                    pointsRet->emplace_back(point.data);
                }
            }
        }
    }

}
