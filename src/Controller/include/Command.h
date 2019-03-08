//
// Created by Wallyn Valentin on 17/02/2019.
//

#ifndef QUALITAIR_COMMAND_H
#define QUALITAIR_COMMAND_H


#include <string>
#include "nlohmann/json.hpp"
using json = nlohmann::json;

class Command {
    public:
        enum OutputFormat { HUMAN, JSON, HTML };
        static const std::unordered_map<std::string, OutputFormat> OutputFormatDictionary;
        struct OutputArguments {
            OutputArguments() = default;
            OutputArguments(std::string outputFile, Command::OutputFormat outputFormat) :
                    outputFile(outputFile), outputFormat(outputFormat) {};
            std::string outputFile;
            OutputFormat outputFormat;
        };

        Command() = default;
        Command(OutputArguments outputArguments);
        virtual void execute() = 0;
        virtual void output() = 0;

    protected:
        OutputArguments outputArguments;

        virtual void to_json(json& j) const = 0;
        virtual void from_json(const json& j) = 0;

        friend void to_json(json& j, const Command& command);
        friend void from_json(const json& j, Command& command);
};


#endif //QUALITAIR_COMMAND_H
