//
// Created by student on 28.12.2019.
//

#include "ThingsManager.h"

ThingsManager::~ThingsManager() {
    delete things;
}

ThingsManager::ThingsManager(ThingsRepository *things)
: things(things)
{
}

void ThingsManager::addThing(Thing_ptr thing) {
    if(things->checkPresence(thing)){
        throw ThingException("The thing has been already inputed to the repository");
    }
    else{
        things->add(thing);
    }
}

void ThingsManager::removeThing(Thing_ptr thing) {
    if(!things->checkPresence(thing)){
        throw ThingException("The thing has been already removed from the repository");
    }
    else{
        things->remove(thing);
    }

}

std::string ThingsManager::getAllThingInfo() {
    return things->getAll();
}

void ThingsManager::changeCharge(Thing_ptr thing, double newCharge) {
    things->changeCharge(thing, newCharge);
}
