#include <iostream>
#include "easylogging++.h"
#include "../src/Controller/include/SensorsCommand.h"

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




/**
 * Main function
 * @param {int} argc - Argument count
 * @param {char**} argv - Argument string array
 * @return {int}
 */
int main(int argc, char **argv) {
    cout << "Hello world!" << endl;
    BBox b = BBox(12,89,45,65);
    SensorsCommand sensorsCommand = SensorsCommand(b);
    sensorsCommand.execute();

    return 0;
}

