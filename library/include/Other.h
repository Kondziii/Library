//
// Created by student on 22.12.2019.
//

#ifndef BIBLIOTEKA_OTHER_H
#define BIBLIOTEKA_OTHER_H


#include "RenterTypes.h"

class Other : public RenterTypes{

public:
    int getMaxThings() override;
    int getFreeRentDuration() override;
    std::string getTypeName();
    ~Other() override;
};


#endif //BIBLIOTEKA_OTHER_H
