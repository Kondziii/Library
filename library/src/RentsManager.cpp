//
// Created by student on 28.12.2019.
//

#include "RentsManager.h"

RentsManager::~RentsManager() {
    delete rents;
}

RentsManager::RentsManager(RentsRepository *rents)
: rents(rents)
{
}

void RentsManager::addRent(Renter_ptr renter, Thing_ptr thing, Time_ptr begin) {
    if(rents->isRented(thing)){
        throw RentException("This thing has been already rented");
    }

    if(renter->getNumberOfPossibleRents()==0){
        throw RentException("This renter can't rent more things");
    }
    Rent_ptr rent(new Rent(renter, thing, begin));
    rents->add(rent);
}

void RentsManager::removeRent(Thing_ptr thing) {
    if(!rents->isRented(thing)){
        throw RentException("This thing has already been returned");
    }
    Rent_ptr rent=rents->findThingRental(thing);
    rents->remove(rent);
}

std::vector<Rent_ptr> RentsManager::getAllRenterRents(Renter_ptr renter) {
    return rents->getAllRenterRents(renter);
}

void RentsManager::extendRental(Thing_ptr thing, Time_ptr time) {
    Rent_ptr rent=rents->findThingRental(thing);
    rent->extendFreeRental(time);
}

std::string RentsManager::getAllRentInfo() {
    return rents->getAll();
}
