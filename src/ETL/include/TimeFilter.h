//
// Created by Wallyn Valentin on 17/02/2019.
//

#ifndef QUALITAIR_TIMEFILTER_H
#define QUALITAIR_TIMEFILTER_H


#include "Filter.h"
#include <ctime>

class TimeFilter : public Filter {
    public:
            void applyTo(QueryBuilder &qb) override;

            void setStart(std::time_t start);
            void setEnd(std::time_t end);
            void setInterval(std::time_t start, std::time_t end);
    
            TimeFilter & operator = ( TimeFilter other );
            TimeFilter ( const TimeFilter & other );
            TimeFilter ();
            virtual ~TimeFilter ( );
    
    protected:
            friend void swap(TimeFilter & first, TimeFilter & second);
    
            std::time_t start;
            std::time_t end;
            bool startDefined;
            bool endDefined;
};


#endif //QUALITAIR_TIMEFILTER_H
