//
// Created by student on 23.12.2019.
//

#include <sstream>
#include "ThingException.h"
#include "Thing.h"

Thing::Thing(std::string id, std::string title, double baseRentCharge)
        : id(id), title(title), baseRentCharge(baseRentCharge)
{
    if(id.size()==0){
        throw ThingException("Incorrect id");
    }
    if(title.size()==0){
        throw ThingException("Incorrect title");
    }
    if(baseRentCharge<=0){
        throw ThingException("Incorrect value of charge");
    }
}

const std::string &Thing::getId() const {
    return id;
}

double Thing::getBaseRentCharge() const {
    return baseRentCharge;
}

const std::string &Thing::getTitle() const {
    return title;
}

std::string Thing::getInfo() {
    std::stringstream sout;
    sout<<id<<" "<<title<<" ";
    return sout.str();
}

double Thing::getActualCharge() {
    return getBaseRentCharge();
}

Thing::~Thing() {

}

void Thing::setBaseRentCharge(double baseRentCharge) {
    Thing::baseRentCharge = baseRentCharge;
}






