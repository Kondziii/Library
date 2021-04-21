//
// Created by student on 27.12.2019.
//

#include <sstream>
#include "RentersRepository.h"
#include "RenterException.h"

std::string RentersRepository::getAll() {
    std::stringstream sout;
    for(auto it: elements){
        sout<<it->getAll(false);
        sout<<"\n";
    }
    return sout.str();
}

void RentersRepository::changeRenterType(Renter_ptr renter, type type) {
    for(auto it: elements){
        if(it==renter){
            it->setRenterType(type);
            return;
        }
    }
    throw RenterException("Cannot change the type of renter which isn't in repository");
}

RentersRepository::~RentersRepository() {

}

std::ostream &operator<<(std::ostream &os, RentersRepository &repo) {
    for(auto it: repo.getElements()) {
        os << it->getAll(false);
        os << "\n";
    }
    return os;
}
