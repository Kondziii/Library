//
// Created by student on 28.12.2019.
//

#ifndef BIBLIOTEKA_RENTSMANAGER_H
#define BIBLIOTEKA_RENTSMANAGER_H


#include "RentsRepository.h"

class RentsManager {
    RentsRepository* rents;
public:
    explicit RentsManager(RentsRepository* rents);
    virtual ~RentsManager();
    std::vector<Rent_ptr> getAllRenterRents(Renter_ptr renter);
    std::string getAllRentInfo();
    void addRent(Renter_ptr renter, Thing_ptr thing, Time_ptr begin);
    void removeRent(Thing_ptr thing);
    void extendRental(Thing_ptr thing, Time_ptr time);
};


#endif //BIBLIOTEKA_RENTSMANAGER_H
