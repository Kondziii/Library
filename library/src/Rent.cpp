//
// Created by student on 23.12.2019.
//

#include "Rent.h"
#include "RentException.h"
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/random_generator.hpp>
using namespace boost::local_time;
using namespace boost::posix_time;
using namespace std;

Rent::~Rent() {

}

Rent::Rent(Renter_ptr renter, Thing_ptr thing, Time_ptr begin)
        : renter(renter), thing(thing), begin(begin), end(nullptr), rentCost(0), chargeDuration(0), numberOfExtends(0)
{
    if(renter==nullptr || thing== nullptr){
        throw RentException("Null renter or thing");
    }
    ID=boost::uuids::random_generator()();
    renter->addRent(this);
    freeDuration=renter->getFreeRentDuration();
}

std::string Rent::rentInfo(bool renterInfo) {
    std::stringstream info;
    info<<ID<<" ";
    info<<*begin<<" ";
    if(end== nullptr){
        info<<getRentDuration()<<" ";
    }
    else{
        info<<*end<<" ";
    }

    if(renterInfo){
        info<<renter->getAll(false)<<" ";
    }
    info<<thing->getInfo();
    if(end!= nullptr){
        info<<" Rent cost: "<<getRentCost();
    }
    return info.str();
}

int Rent::getRentDuration() {
    if(end== nullptr) return 0;
    if(end->date()<begin->date())throw RentException("Incorrect dates");
    return (end->date()-begin->date()).days()+1;
}

double Rent::getRentCost() {
    if(end== nullptr){
        return 0;
    }
    int duration= this->getRentDuration()-freeDuration;
    if(duration>0){
        rentCost=(duration+chargeDuration)*thing->getActualCharge();
    }
    else{
        rentCost=chargeDuration*thing->getActualCharge();
    }
    rentCost=rentCost*100;
    rentCost=(int)rentCost;
    rentCost=rentCost/100;
    return rentCost;
}

void Rent::endRent() {
    renter->endRent(this);
    time_zone_ptr zone(new posix_time_zone("CET"));
    end = Time_ptr (new local_date_time(local_sec_clock::local_time(zone)));
    if(*end<*begin){
        throw RentException("Incorrect dates");
    }
}

void Rent::extendFreeRental(Time_ptr time) {
    if(time->date()<begin->date())throw RentException("Incorrect date to extend rental");;
    int TimeBeforeExtension= freeDuration+chargeDuration-numberOfExtends-((time->date()-begin->date()).days()+1);
    if(TimeBeforeExtension<5){
        if(TimeBeforeExtension<0){
            chargeDuration+=-TimeBeforeExtension;
        }
        freeDuration+=renter->getFreeRentDuration();
    }
    else{
        throw RentException("Too early to extend this rental");
    }
    numberOfExtends++;
}

const Renter_ptr &Rent::getRenter() const {
    return renter;
}

const Thing_ptr &Rent::getThing() const {
    return thing;
}

int Rent::getChargeDuration() const {
    return chargeDuration;
}

std::string Rent::getId() const {
    std::stringstream sout;
    sout<<ID;
    return sout.str();
}