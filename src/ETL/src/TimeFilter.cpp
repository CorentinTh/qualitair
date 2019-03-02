//
// Created by Wallyn Valentin on 17/02/2019.
//

#include "../include/TimeFilter.h"

void TimeFilter::applyTo(QueryBuilder &qb) {
    if (this->startDefined){
        qb.andWhere("date > ?").bind(this->start);
    }
    if (this->endDefined){
        qb.andWhere("date < ?").bind(this->end);
    }
}

void TimeFilter::setStart(std::time_t start) {
    this->start = start;
    this->startDefined = true;
}

void TimeFilter::setEnd(std::time_t end) {
    this->end = end;
    this->endDefined = true;
}

void TimeFilter::setInterval(std::time_t start, std::time_t end) {
    this->start = start;
    this->end = end;
    this->startDefined = true;
    this->endDefined = true;
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
