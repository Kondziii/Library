//
// Created by student on 27.12.2019.
//

#include <sstream>
#include <ThingException.h>
#include "ThingsRepository.h"

std::string ThingsRepository::getAll() {
    std::stringstream sout;
    for(auto it:elements){
        sout<<it->getInfo()<<"\n";
    }
    return sout.str();
}

void ThingsRepository::changeCharge(Thing_ptr thing, double newCharge) {
    for(auto it:elements){
        if(it==thing){
            it->setBaseRentCharge(newCharge);
            return;
        }
    }
    throw ThingException("Cannot change the price of element which isn't in repository");
}

ThingsRepository::~ThingsRepository() {

}

std::ostream &operator<<(std::ostream &os, ThingsRepository &repo) {
    for(auto it: repo.getElements()) {
        os << it->getInfo();
        os << "\n";
    }
    return os;
}
