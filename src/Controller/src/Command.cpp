//
//        ----[  QUALIT'AIR  ]----
//
//    Marsaud Menseau Thomasset Wallyn
//  Copyright © 2019 - All right reserved
//

#include "../include/Command.h"

const std::unordered_map<std::string, Command::OutputFormat> Command::OutputFormatDictionary{
        {"HUMAN", OutputFormat::HUMAN},
        {"JSON",  OutputFormat::JSON},
        {"HTML",  OutputFormat::HTML}
};

Command::Command(OutputArguments outputArguments) : outputArguments(outputArguments) {
}

void to_json(json &j, const Command &command) {
    command.to_json(j);
}

void from_json(const json &j, Command &command) {
    command.from_json(j);
}