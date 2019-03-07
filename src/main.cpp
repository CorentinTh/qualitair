#include <iostream>
#include <iomanip>
#include "easylogging++.h"


INITIALIZE_EASYLOGGINGPP

/**
 * "Please note that INITIALIZE_EASYLOGGINGPP should be used once and once-only otherwise you will end up getting
 * compilation errors. This is definiting several extern variables. This means it can be defined only once per
 * application. Best place to put this initialization statement is in file where int main(int, char**) function is
 * defined, right after last include statement."
 *
 * On le mettra qqlque part dans le controler pour avoir un main vide et propre.
 */


#include "globals.h"
#include "ETL/include/ETL.h"
#include "Data/include/ConnectionFactory.h"
#include "Data/include/Measurement.h"

using namespace std;


template<typename T>
bool areVectorEquals(vector<T> *a, vector<T> *b) {
    if (a->size() != b->size()) return false;

    for (unsigned int i = 0; i < a->size(); ++i) {
        auto va = *a->at(i);
        auto vb = *b->at(i);

        if (va != vb) return false;
    }

    return true;
}

/**
 * Main function
 * @param {int} argc - Argument count
 * @param {char**} argv - Argument string array
 * @return {int}
 */
int main(int argc, char **argv) {
    ConnectionFactory::setDatabase("../tests/data/dbmock.sqlite");

    ETL etl = ETL::getInstance();

    auto result = (pointCollection *) etl.getData(
            {
                    {"type",                 ETL::MEASURE},
                    {"hasStart",             true},
                    {"hasEnd",               true},
                    {"hasBBox",              true},
                    {"hasAttributes",        true},
                    {"doInterpolation",      true},
                    {"attributes",           {"3"}},
                    {"start",                1550150000},
                    {"end",                  1550159000},
                    {"BBox",                 {
                                              {"left",      4},
                                                     {"right",    5},
                                                     {"top",  45.8},
                                                     {"bottom", 45.5}
                                             }},
                    {"spatialGranularity",   0.5},
                    {"temporalGranularity",  1000},
                    {"minimalInterDistance", {
                                              {"longitude", 50},
                                                     {"latitude", 50},
                                                     {"time", 10000}
                                             }}
            });


    cout << "{" << endl;
    for (auto &c : *result) {
        cout << "\t{" << endl;
        for (auto &r : c) {
            cout << "\t\t{";
            for (auto &d : r) {
                cout << "{";
                for (auto &v : d) {
                    cout << "{\"";
                    cout << v.first << "\", ";
                    cout << fixed << setprecision(3) << v.second << " ";
                    cout << "}, ";
                }
                cout << "}, ";

            }
            cout << "}, " << endl;
        }
        cout << "\t}, " << endl;
    }
    cout << "}" << endl;



//    for (auto &m   : *result) {
//        cout << "new Measurement(";
//        cout << m->getTimestamp() << ", { \"";
//        cout << m->getSensor().getId() << "\", ";
//        cout << setprecision(9) << m->getSensor().getLatitude() << ", ";
//        cout << setprecision(9) << m->getSensor().getLongitude() << ",\" ";
//        cout << m->getSensor().getDescription() << "\"}, {\"";
//        cout << m->getAttribute().getId() << "\", \"";
//        cout << m->getAttribute().getUnit() << "\", \"";
//        cout << m->getAttribute().getDescription() << "\"}, ";
//        cout << setprecision(9) << m->getValue() << "), ";
//        cout << endl;
//    }

    return 0;
}

