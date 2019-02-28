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

/**
 * Main function
 * @param {int} argc - Argument count
 * @param {char**} argv - Argument string array
 * @return {int}
 */
int main(int argc, char ** argv){
    cout << "Hello world!" << endl;

    Interpolater interpolater;

    std::vector<Measurement> measures = {
            Measurement(1550150156, Sensor("2", 45.7632485, 4.8335574, "Cordelier - Métro"), Attribute("1", "", ""), 5),
            Measurement(1550151014, Sensor("3", 45.762994, 4.833632, "Rue de la république"), Attribute("2", "", ""), 10),
            Measurement(1550158000, Sensor("3", 45.762994, 4.833632, "Rue de la république"), Attribute("2", "", ""), 28),
            Measurement(1550151014, Sensor("147", 28.468412, 14.351684, "Paris - Tour Eiffel"), Attribute("3", "", ""), 1763),// superieur au range
            Measurement(1550151014, Sensor("147", 28.468412, 14.351684, "Paris - Tour Eiffel"), Attribute("1", "", ""), 5),
            Measurement(1550150032, Sensor("147", 28.468412, 14.351684, "Paris - Tour Eiffel"), Attribute("1", "", "") , 5),
            Measurement(1550150032, Sensor("147", 28.468412, 14.351684, "Paris - Tour Eiffel"), Attribute("3", "", "") , 1765),
            Measurement(1650158000, Sensor("3", 45.762994, 4.833632, "Rue de la république"), Attribute("2", "", ""), 28)
    };

    interpolater.interpolate(measures, {});

    return 0;
}

