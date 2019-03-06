//
// Created by vwallyn on 05/03/19.
//

#ifndef QUALITAIR_SENSORSCOMMAND_H
#define QUALITAIR_SENSORSCOMMAND_H

#include "Command.h"
#include "../../Data/include/BBox.h"

class SensorsCommand : public Command{
    public:
    
        SensorsCommand & operator = ( SensorsCommand other );
        SensorsCommand ( const SensorsCommand & other );
        SensorsCommand ( BBox bbox );
        virtual ~SensorsCommand ( );
    
        void execute() override;
    
        void output() override;
    
    protected:
        friend void swap(SensorsCommand & first, SensorsCommand & second);
        friend void to_json(json& j, const SensorsCommand& command);
        friend void from_json(const json& j, SensorsCommand& command);

        BBox bbox;
};


#endif //QUALITAIR_SENSORSCOMMAND_H
