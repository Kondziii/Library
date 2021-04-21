//
// Created by student on 28.12.2019.
//

#include <RenterException.h>
#include "RentersManager.h"

RentersManager::~RentersManager() {
    delete renters;
}

RentersManager::RentersManager(RentersRepository *renters)
: renters(renters)
{
}

void RentersManager::addRenter(Renter_ptr renter) {
    if(renters->checkPresence(renter)){
        throw RenterException("This renter has already been added to the repository");
    }
    else{
        renters->add(renter);
    }
}

void RentersManager::removeRenter(Renter_ptr renter) {
    if(!renters->checkPresence(renter)){
        throw RenterException("This renter has already been removed from the repository");
    }
    else{
        renters->remove(renter);
    }
}

std::string RentersManager::getAllRenterInfo() {
    return renters->getAll();
}

void RentersManager::changeRenterType(Renter_ptr renter, type type) {
    renters->changeRenterType(renter, type);
}
