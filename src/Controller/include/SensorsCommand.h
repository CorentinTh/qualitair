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
        SensorsCommand ( BBox bbox, OutputArguments outputArguments );
        virtual ~SensorsCommand ( );
    
        void execute() override;

    protected:
        friend void swap(SensorsCommand & first, SensorsCommand & second);
        virtual void to_json(json& j) const override;
        virtual void from_json(const json& j) override;

        BBox bbox;
};


#endif //QUALITAIR_SENSORSCOMMAND_H
