//
// Created by Wallyn Valentin on 17/02/2019.
//

#include "../include/Command.h"

void to_json(json& j, const Command& command) {
    command.to_json(j);
}

void from_json(const json& j, Command& command) {
    command.from_json(j);
}