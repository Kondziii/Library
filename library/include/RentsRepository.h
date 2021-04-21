//
// Created by student on 27.12.2019.
//

#ifndef BIBLIOTEKA_RENTSREPOSITORY_H
#define BIBLIOTEKA_RENTSREPOSITORY_H


#include "Rent.h"
#include "Repository.h"

class RentsRepository : public Repository<Rent_ptr>{

public:
    bool isRented(Thing_ptr thing);
    std::vector<Rent_ptr> getAllRenterRents(Renter_ptr renter);
    std::string getAll() override;
    Renter_ptr getRenterForRentedThing(Thing_ptr thing);
    Rent_ptr findThingRental(Thing_ptr thing);
    ~RentsRepository() override;
};

std::ostream& operator << (std::ostream & os, RentsRepository & repo);

#endif //BIBLIOTEKA_RENTSREPOSITORY_H