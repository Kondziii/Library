//
// Created by student on 27.12.2019.
//

#ifndef BIBLIOTEKA_THINGSREPOSITORY_H
#define BIBLIOTEKA_THINGSREPOSITORY_H


#include "Thing.h"
#include "Repository.h"

class ThingsRepository : public Repository<Thing_ptr>{
public:
    std::string getAll();
    void changeCharge(Thing_ptr thing, double newCharge);
    virtual ~ThingsRepository();

};

std::ostream& operator << (std::ostream & os, ThingsRepository & repo);

#endif //BIBLIOTEKA_THINGSREPOSITORY_H
