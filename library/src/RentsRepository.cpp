//
// Created by student on 27.12.2019.
//

#include "RentsRepository.h"

bool RentsRepository::isRented(Thing_ptr thing) {
    for(auto it: elements){
        if(it->getThing()==thing){
            return true;
        }
    }
    return false;
}

Renter_ptr RentsRepository::getRenterForRentedThing(Thing_ptr thing) {
    for(auto it: elements){
        if(it->getThing()==thing){
            return it->getRenter();
        }
    }
    return nullptr;
}

std::vector<Rent_ptr> RentsRepository::getAllRenterRents(Renter_ptr renter) {
    std::vector<Rent_ptr> rents;
    for(auto it: elements){
        if(it->getRenter()==renter){
            rents.push_back(it);
        }
    }
    return rents;
}

std::string RentsRepository::getAll() {
    std::stringstream sout;
    for(auto it: elements){
        sout<<it->rentInfo()<<"\n";
    }
    return sout.str();
}

Rent_ptr RentsRepository::findThingRental(Thing_ptr thing) {
    for(auto it:elements){
        if(it->getThing()==thing){
            return it;
        }
    }
    return nullptr;
}

RentsRepository::~RentsRepository() {

}

std::ostream &operator<<(std::ostream &os, RentsRepository &repo) {
    for(auto it: repo.getElements()) {
        os << it->rentInfo();
        os << "\n";
    }
    return os;
}
