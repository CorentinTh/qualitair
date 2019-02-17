//
// Created by Wallyn Valentin on 17/02/2019.
//

#ifndef QUALITAIR_IDATAPROCESS_H
#define QUALITAIR_IDATAPROCESS_H


class IDataProcess {
    public:
        virtual ~IDataProcess() {}
        //TODO params
        virtual void apply() = 0;
};


#endif //QUALITAIR_IDATAPROCESS_H
