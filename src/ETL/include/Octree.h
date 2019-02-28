//
// Created by cthomasset on 27/02/19.
//

#ifndef QUALITAIR_QUADTREE_H
#define QUALITAIR_QUADTREE_H

#include <vector>
#include <iostream>
#include <algorithm>

#define NODE_COUNT 8

using namespace std;

namespace OT {

    /**
     * Define a point structure to store data and coordinates
     */
    typedef struct {
        int x;
        int y;
        int z;
        void *data;
    } point_t;

    /**
     * Class Boundary
     */
    class Boundary {
    public:

        /**
         * Boundary constructor
         * @param {int} x0 - Left bound
         * @param {int} y0 - Top bound
         * @param {int} x1 - Right bound
         * @param {int} y1 - Bottom bound
         */
        explicit Boundary(int x0 = 0, int y0 = 0, int z0 = 0, int x1 = 0, int y1 = 0, int z1 = 0);

        /**
         * Check if a point is within the boundaries
         * @param {node_t} node - A node to check if he is contained in the boundaries
         * @return {bool} - True if the node is within the boundaries
         */
        bool contains(const point_t &point) const;

        /**
         * Check if a boundary intersects with another boundary
         * @param {Boundary *} b - A boundary to check the intersection
         * @return {bool} - True if the boundary intersects
         */
        bool intersects(const Boundary *b) const;

        /**
         * Left bound getter
         * @return {int} - Left bound value
         */
        int getX0() const;

        /**
         * Top bound getter
         * @return {int} - Top bound value
         */
        int getY0() const;

        /**
         * Right bound getter
         * @return {int} - Right bound value
         */
        int getX1() const;

        /**
         * Bottom bound getter
         * @return {int} - Bottom bound value
         */
        int getY1() const;

        int getZ0() const;

        int getZ1() const;

    private:
        int x0;
        int y0;
        int x1;
        int y1;
        int z0;
        int z1;
    };


    /**
     * Class Quadtree
     */
    class Octree {
    public:

        /**
         * Quadtree constructor
         * @param {Boundary *} boundary - Default boundary
         * @param {int} maxCapacity - Max capacity of points in a tree node
         * @param {vector<node_t>*} initNodes - Pointer to vector of default node to insert in the quadtree
         */
        explicit Octree(Boundary *boundary, int maxCapacity = 16, vector<point_t> *initNodes = nullptr);

        /**
         * Quadtree destructor
         */
        virtual ~Octree();

        /**
         * Insert a new node in the quadtree
         * @contract Don't insert more than maxCapacity node at exactly the same spot
         * @param {node_t} node - Node to insert
         * @return {bool} - Return true if the element as been inserted
         */
        bool insert(const point_t &point);

        /**
         * Query data in the quadtree
         * @param {Boundary *} range - Range to retrieve points from
         * @return {vector<void *>*} - Collection of data in the given range
         */
        vector<void *> *query(Boundary *range);

    private:
        /**
         * Divide the quadtree node in 4 sub-nodes
         */
        void divide();

        /**
         * Query method for internal recursive search
         * @param {Boundary *} range - Range to retrieve points from
         * @param {vector<void *>*} pointsRet - Collection of data in the given range
         */
        void query(Boundary *range, vector<void *> *pointsRet);


        enum {
            NWT, // North west top
            NET, // North east top
            SWT, // South west top
            SET, // South east top
            NWB, // North west bottom
            NEB, // North east bottom
            SWB, // South west bottom
            SEB, // South east bottom
        };

        Octree *nodes[NODE_COUNT];
        vector<point_t> points;
        Boundary *container;
        int maxCapacity;
        int capacity = 0;
        bool isDivided = false;
    };

}


#endif //QUALITAIR_QUADTREE_H
