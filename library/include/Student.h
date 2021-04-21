//
// Created by student on 22.12.2019.
//

#ifndef BIBLIOTEKA_STUDENT_H
#define BIBLIOTEKA_STUDENT_H


#include "RenterTypes.h"

class Student : public RenterTypes{

public:
    int getMaxThings() override;
    int getFreeRentDuration() override;
    std::string getTypeName();
    ~Student() override;
};


#endif //BIBLIOTEKA_STUDENT_H

