//
// Created by Wallyn Valentin on 17/02/2019.
//

#include "../include/TimeFilter.h"
#include <stdexcept>


void TimeFilter::applyTo(QueryBuilder &qb) {
    if (this->startDefined){
        qb.andWhere("timestamp > ?").bind(this->start);
    }
    if (this->endDefined){
        qb.andWhere("timestamp < ?").bind(this->end);
    }
}

void TimeFilter::setStart(std::time_t start) {
    if (!this->endDefined || (this->endDefined && start < this->end)){
        this->start = start;
        this->startDefined = true;
    }
    else{
        throw std::logic_error("La date de debut est supérieure ou égale à la date de fin déjà renseignée");
    }
}

void TimeFilter::setEnd(std::time_t end) {
    if (!this->startDefined || (this->startDefined && this->start < end)){
        this->end = end;
        this->endDefined = true;
    }
    else{
        throw std::logic_error("La date de fin est inférieure ou égale à la date de début déjà renseignée");
    }
}

void TimeFilter::setInterval(std::time_t start, std::time_t end) {
    if (start < end){
        this->start = start;
        this->end = end;
        this->startDefined = true;
        this->endDefined = true;
    }
    else{
        throw std::logic_error("L'intervalle passé en paramètre de setInterval n'est pas correct");
    }
}

TimeFilter &TimeFilter::operator=(TimeFilter other) {
    return *this;
}

TimeFilter::TimeFilter(const TimeFilter &other) {

}

TimeFilter::TimeFilter() {
    this->startDefined = false;
    this->endDefined = false;
}

TimeFilter::~TimeFilter() {

}
