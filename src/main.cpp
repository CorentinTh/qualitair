#include <iostream>
#include "easylogging++.h"

using namespace std;

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
#include "ETL/include/Interpolater.h"
#include <iomanip>

/**
 * Main function
 * @param {int} argc - Argument count
 * @param {char**} argv - Argument string array
 * @return {int}
 */
int main(int argc, char **argv) {
    cout << "Hello world!" << endl;

    Interpolater interpolater;

    std::vector<Measurement *> measures = {
            new Measurement(0, Sensor("1", 0, 0, ""), Attribute("1", "", ""), 5),
            new Measurement(0, Sensor("1", 20, 20, ""), Attribute("1", "", ""), 10),
            new Measurement(0, Sensor("1", 0, 0, ""), Attribute("2", "", ""), 5),
            new Measurement(0, Sensor("1", 20, 20, ""), Attribute("2", "", ""), 10),
            new Measurement(20, Sensor("1", 0, 0, ""), Attribute("1", "", ""), 10),
            new Measurement(20, Sensor("1", 20, 20, ""), Attribute("1", "", ""), 5),
            new Measurement(20, Sensor("1", 0, 0, ""), Attribute("2", "", ""), 10),
            new Measurement(20, Sensor("1", 20, 20, ""), Attribute("2", "", ""), 5),
    };

    auto data = interpolater.interpolate(measures, {
            {"spatialGranularity",   10},
            {"temporalGranularity",  10},
            {"area",                 {0, 0, 20, 20}},
            {"timeRange",            {0, 20}},
            {"minimalInterDistance", {
                                      {"longitude", 5000},
                                         {"latitude", 5000},
                                            {"time", 50}
                                     }}
    });

    cout << "{";
    for (auto &c : *data) {
        cout << "{";
        for (auto &r : c) {
            cout << "{";
            for (auto &d : r) {
                cout << "{";
                for (auto &v : d) {
                    cout << "{\"";
                    cout << v.first << "\", ";
                    cout << fixed << setprecision(3) << d.find("1")->second << " ";
                    cout << "}, ";
                }
                cout << "}, ";

            }
            cout << "}, " << endl;
        }
        cout << "}, " << endl;
    }
    cout << "}" << endl;


    return 0;
}

