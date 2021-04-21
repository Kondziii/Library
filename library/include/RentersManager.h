//
// Created by student on 28.12.2019.
//

#ifndef BIBLIOTEKA_RENTERSMANAGER_H
#define BIBLIOTEKA_RENTERSMANAGER_H


#include "RentersRepository.h"

class RentersManager {
    RentersRepository* renters;
public:
    explicit RentersManager(RentersRepository* renters);
    virtual ~RentersManager();
    void addRenter(Renter_ptr renter);
    void removeRenter(Renter_ptr renter);
    std::string getAllRenterInfo();
    void changeRenterType(Renter_ptr renter, type type);
};


#endif //BIBLIOTEKA_RENTERSMANAGER_H
