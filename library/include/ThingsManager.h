//
// Created by student on 28.12.2019.
//

#ifndef BIBLIOTEKA_THINGSMANAGER_H
#define BIBLIOTEKA_THINGSMANAGER_H


#include "ThingsRepository.h"

class ThingsManager {
    ThingsRepository* things;
public:
    explicit ThingsManager(ThingsRepository* things);
    virtual ~ThingsManager();
    void addThing(Thing_ptr thing);
    void removeThing(Thing_ptr thing);
    std::string getAllThingInfo();
    void changeCharge(Thing_ptr thing, double newCharge);
};

#endif //BIBLIOTEKA_THINGSMANAGER_H
