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
        throw std::logic_error("starting date must be before ending date");
    }
}

void TimeFilter::setEnd(std::time_t end) {
    if (!this->startDefined || (this->startDefined && this->start < end)){
        this->end = end;
        this->endDefined = true;
    }
    else{
        throw std::logic_error("Ending date must be after starting date");
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
        throw std::logic_error("Starting date must be before ending date");
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
