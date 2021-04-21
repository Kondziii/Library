//
// Created by student on 22.12.2019.
//

#ifndef BIBLIOTEKA_PROFESSOR_H
#define BIBLIOTEKA_PROFESSOR_H


#include "RenterTypes.h"

class Professor : public RenterTypes {

public:
    int getMaxThings() override;
    int getFreeRentDuration() override;
    std::string getTypeName();
    ~Professor() override;
};


#endif //BIBLIOTEKA_PROFESSOR_H
