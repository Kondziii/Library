//
// Created by student on 22.12.2019.
//

#ifndef BIBLIOTEKA_RENTERTYPES_H
#define BIBLIOTEKA_RENTERTYPES_H


#include <memory>

class RenterTypes {
public:
    virtual int getMaxThings()=0;
    virtual int getFreeRentDuration()=0;
    virtual std::string getTypeName()=0;
    virtual ~RenterTypes();
};
typedef std::shared_ptr<RenterTypes> RenterTypes_ptr;


#endif //BIBLIOTEKA_RENTERTYPES_H

