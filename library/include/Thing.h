//
// Created by student on 23.12.2019.
//

#ifndef BIBLIOTEKA_THING_H
#define BIBLIOTEKA_THING_H


#include <string>
#include <memory>
#include "ThingException.h"

class Thing {
    std::string id;
    double baseRentCharge;
    std::string title;

public:
    Thing(std::string id, std::string title, double baseRentCharge);
    virtual ~Thing();
    virtual std::string getInfo();
    virtual double getActualCharge();
    void setBaseRentCharge(double baseRentCharge);
    const std::string &getId() const;
    double getBaseRentCharge() const;
    const std::string &getTitle() const;
};

typedef std::shared_ptr<Thing> Thing_ptr;

#endif //BIBLIOTEKA_THING_H

