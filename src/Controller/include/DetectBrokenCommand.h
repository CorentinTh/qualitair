//
// Created by Wallyn Valentin on 17/02/2019.
//

#ifndef QUALITAIR_DETECTBROKENCOMMAND_H
#define QUALITAIR_DETECTBROKENCOMMAND_H


#include <vector>
#include "Command.h"
#include "../../Data/include/BBox.h"

class DetectBrokenCommand : public Command {
    public:

        DetectBrokenCommand & operator = ( DetectBrokenCommand other );
        DetectBrokenCommand ( const DetectBrokenCommand & other );
        DetectBrokenCommand ( BBox bbox, time_t start, time_t end, std::vector<std::string> attributes, std::vector<std::string> sensors );
        virtual ~DetectBrokenCommand ( );

        void execute() override;

        void output() override;

    protected:
        friend void swap(DetectBrokenCommand & first, DetectBrokenCommand & second);
        friend void to_json(json& j, const DetectBrokenCommand& command);
        friend void from_json(const json& j, DetectBrokenCommand& command);

        BBox bbox;
        time_t start;
        time_t end;
        std::vector<std::string> attributes;
        std::vector<std::string> sensors;


};


#endif //QUALITAIR_DETECTBROKENCOMMAND_H
