//
//        ----[  QUALIT'AIR  ]----
//
//    Marsaud Menseau Thomasset Wallyn
//  Copyright © 2019 - All right reserved
//


#include "easylogging++.h"
#include "Controller/include/Controller.h"

INITIALIZE_EASYLOGGINGPP


int main(int argc, char **argv) {
    START_EASYLOGGINGPP(argc, argv);

    Controller controller(argv);
    controller.execute();

    return 0;
}

