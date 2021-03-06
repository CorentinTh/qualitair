//
//        ----[  QUALIT'AIR  ]----
//
//    Marsaud Menseau Thomasset Wallyn
//  Copyright © 2019 - All right reserved
//

#include <iomanip>
#include <iostream>
#include "easylogging++.h"
#include "../include/Controller.h"
#include "../include/StatsCommand.h"
#include "../include/CLIParser.h"
#include "../include/IngestCommand.h"
#include "../include/SpikesCommand.h"
#include "../include/DetectBrokenCommand.h"
#include "../include/DetectSimCommand.h"
#include "../include/SensorsCommand.h"
#include "../include/Cache.h"
#include "../../Data/include/ConnectionFactory.h"
#include "../../utils.h"


Controller &Controller::operator=(Controller other) {
    swap(*this, other);
    return *this;
}

Controller::Controller(const Controller &other) {

}

Controller::Controller(char **argv) {
    this->argv = argv;
    config.load();
}

Controller::~Controller() {

}

Command *Controller::parseCommand() {
    CLIParser cliParser(argv);

    Command *command = nullptr;
    std::string verb = cliParser.getVerb();

    ConnectionFactory::setDatabase(cliParser.getArgument("database", config.getDatabaseFilepath()));
    Command::OutputArguments outputArguments(
            cliParser.getArgument("file", "stdout"),
            Command::OutputFormatDictionary.at(cliParser.getArgument("format", "HUMAN"))
    );


    if (verb == "ingest") {
        std::string input = cliParser.getArgument("input", ".");
        command = new IngestCommand(input, outputArguments);
    } else {
        BBox bbox(cliParser.getArgument("bbox"));
        time_t start = utils::parseRFC3339Date(cliParser.getArgument("start"));
        time_t end = utils::parseRFC3339Date(cliParser.getArgument("end"));
        std::vector<std::string> attributes = utils::unjoinString(cliParser.getArgument("attributes"));
        std::vector<std::string> sensors = utils::unjoinString(cliParser.getArgument("sensors"));

        if (verb == "stats") {
            try {
                std::string statType = cliParser.getMandatoryArgument();
                for (auto &c: statType) c = toupper(c);
                StatsCommand::StatEnum stat = StatsCommand::StatDictionary.at(statType);
                json interpolationConfig = {
                        {"spatialGranularity",  config.getSpatialGranularity()},
                        {"temporalGranularity", config.getTemporalGranularity()}
                };
                command = new StatsCommand(stat, bbox, start, end, attributes, sensors, outputArguments, interpolationConfig);
            }
            catch (std::out_of_range) {
                LOG(ERROR) << "Unknown stat type";
            }
            catch (std::exception) {
                LOG(ERROR) << "Missing mandatory argument \"stat type\".";
            }
        } else if (verb == "spikes") {


            try {
                std::string attribute = cliParser.getMandatoryArgument();
                SpikesCommand::SpikeDetectionConfiguration detectionConfig = {
                        config.getSpikesValueThreshold(),
                        (unsigned int) config.getSpikesTimeThreshold(),
                        (unsigned int) config.getSpikesMinimalArea()
                };
                json interpolationConfig = {
                        {"spatialGranularity",  config.getSpatialGranularity()},
                        {"temporalGranularity", config.getTemporalGranularity()}
                };
                command = new SpikesCommand(attribute, bbox, start, end, sensors, detectionConfig, outputArguments, interpolationConfig);
            }
            catch (std::exception) {
                LOG(ERROR) << "Missing mandatory argument \"attribute\".";
            }
        } else if (verb == "broken") {
            command = new DetectBrokenCommand(bbox, start, end, attributes, sensors, config.getBrokenTime(),
                                              config.getAdmissibleRanges(), outputArguments);
        } else if (verb == "similarities") {
            std::string thresholdStr = cliParser.getArgument("threshold");
            double threshold = thresholdStr.empty() ? config.getSimilarityThreshold() : std::stod(thresholdStr);

            command = new DetectSimCommand(bbox, start, end, attributes, sensors, threshold, outputArguments);
        } else if (verb == "sensors") {
            command = new SensorsCommand(bbox, outputArguments);
        } else {
            LOG(ERROR) << "Unknown verb \"" << verb << "\".";
        }


    }

    return command;
}

void Controller::execute() {
    TIMED_FUNC(objTimer);
    Command *command = parseCommand();
    if (command == nullptr) {
        printHelp();
        return;
    }
    std::cout << "here" << std::endl;

    Cache cache;
    json *cached = cache.get(*command);
    if (cached == nullptr) {
        command->execute();
    } else {

        // TODO store & pass to correct view instead of printing json ?
        LOG(WARNING) << "Cached command, showing previous data (if necessary, delete cache at /tmp/.qualitair_cache) : ";
        LOG(INFO) << *cached;
    }
}


void Controller::printHelp() const {
    std::cout << "    ______      __    __       ___       __       __  .___________.__     ___       __  .______      \n"
                 "   /  __  \\    |  |  |  |     /   \\     |  |     |  | |           (_ )   /   \\     |  | |   _  \\     \n"
                 "  |  |  |  |   |  |  |  |    /  ^  \\    |  |     |  | `---|  |----`|/   /  ^  \\    |  | |  |_)  |    \n"
                 "  |  |  |  |   |  |  |  |   /  /_\\  \\   |  |     |  |     |  |         /  /_\\  \\   |  | |      /     \n"
                 "  |  `--'  '--.|  `--'  |  /  _____  \\  |  `----.|  |     |  |        /  _____  \\  |  | |  |\\  \\----.\n"
                 "   \\_____\\_____\\\\______/  /__/     \\__\\ |_______||__|     |__|       /__/     \\__\\ |__| | _| `._____|\n"
                 "                                                                                                     \n" << std::endl;
    std::cout << userManual << std::endl;
}

std::string Controller::userManual = "qualitair [OPTIONS] <verb> [VERB OPTIONS]\n"
                                     "\n"
                                     "\n"
                                     "    [OPTIONS]   --database=FILE\n"
                                     "                    Spécifie le fichier de base de données à utiliser pour les différentes opérations. Si FILE n’est pas défini, utilise le fichier par défaut spécifié dans la configuration.\n"
                                     "\n"
                                     "                --format=TYPE\n"
                                     "                    Spécifie le type de sortie parmi HUMAN (facilement lisible par l’humain), JSON et HTML. Si TYPE n’est pas défini, HUMAN est choisi par défaut.\n"
                                     "\n"
                                     "                --file=FILE\n"
                                     "                    Spécifie le fichier de sortie dans le cas d’une sortie HTML. Si le format de sortie n’est pas HTML, cette option est ignorée.\n"
                                     "\n"
                                     "\n"
                                     "        <verb>  spikes <ATTRIBUTE> [--bbox] [--start] [--end] [--sensors]\n"
                                     "                Détecte les pics de pollution pour un attribut.\n"
                                     "\n"
                                     "                stats <TYPE> [--bbox] [--start] [--end] [--attributes] [--sensors]\n"
                                     "                    Affiche les informations agrégées selon le type spécifié (minimum/maximum, moyenne, écart-type et ATMO.) \n"
                                     "\n"
                                     "                similarities  [--threshold] [--bbox] [--start] [--end] [--attributes] [--sensors]\n"
                                     "                    Affiche les capteurs ayant des comportements similaires.\n"
                                     "\n"
                                     "                broken [--bbox] [--start] [--end] [--attributes] [--sensors]\n"
                                     "                    Affiche les périodes où chaque capteur a été en panne.\n"
                                     "\n"
                                     "                ingest [--input=.] \n"
                                     "                    Charge tous les fichiers CSV du dossier spécifié  dans le système.\n"
                                     "\n"
                                     "                sensors [--bbox]\n"
                                     "                    Affiche la liste des capteurs dans la zone précisée.";

void swap(Controller &first, Controller &second) {

}
