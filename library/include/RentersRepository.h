//
// Created by student on 27.12.2019.
//

#ifndef BIBLIOTEKA_RENTERSREPOSITORY_H
#define BIBLIOTEKA_RENTERSREPOSITORY_H


#include "Renter.h"
#include "Repository.h"
//#include "RentsRepository.h"

class RentersRepository : public Repository<Renter_ptr>{
public:
    std::string getAll() override;
    void changeRenterType(Renter_ptr renter, type type);
    ~RentersRepository() override;
};

std::ostream& operator << (std::ostream & os, RentersRepository & repo);

#endif //BIBLIOTEKA_RENTERSREPOSITORY_H
