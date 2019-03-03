//
// Created by Wallyn Valentin on 17/02/2019.
//

#include "../include/Controller.h"
#include "../include/StatsCommand.h"

Controller &Controller::operator=(Controller other) {
    return *this;
}

Controller::Controller(const Controller &other) {

}

Controller::Controller() {

}

Controller::~Controller() {

}

Command* Controller::parseCommand() {
    return nullptr;
}
