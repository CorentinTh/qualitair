#include <iostream>
#include "../include/IngestCommand.h"
#include "../../ETL/include/ETL.h"


IngestCommand &IngestCommand::operator=(IngestCommand other) {
    swap(*this, other);
    return *this;
}

IngestCommand::IngestCommand(const IngestCommand &other) {
    input = other.input;
}

IngestCommand::IngestCommand(std::string in) : input(in) {

}

IngestCommand::~IngestCommand() {

}

void IngestCommand::execute() {
    ETL etl = ETL::getInstance();

    long output = etl.ingest(input);
    if(output == 0) {
        std::cout << "Aucun élément n'a été ingéré." << std::endl;
    } else if(output == -1) {
        std::cerr << "Un fichier que vous tentez d'ingérer n'est pas au bon format !" << std::endl;
    } else {
        std::cout << output << " éléments ont été ingéré" << (output > 1 ? "s" : "") << " avec succes !";
    }
}

void IngestCommand::output() {

}

void swap(IngestCommand &first, IngestCommand &second) {
    std::swap(first.input, second.input);
}

void IngestCommand::to_json(json &j) const {

}

void IngestCommand::from_json(const json &j) {

}
