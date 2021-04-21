//
// Created by student on 23.12.2019.
//

#ifndef BIBLIOTEKA_RENT_H
#define BIBLIOTEKA_RENT_H
#include "boost/date_time/local_time/local_time.hpp"
#include "Thing.h"
#include "Renter.h"
#include "RentException.h"
#include <memory>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/uuid/uuid.hpp>

typedef std::shared_ptr<boost::local_time::local_date_time> Time_ptr;
typedef boost::uuids::uuid uuid;
class Rent;
typedef std::shared_ptr<Rent> Rent_ptr;

class Rent {
    uuid ID;
    double rentCost;
    int chargeDuration;
    int freeDuration;
    int numberOfExtends;
    Time_ptr begin;
    Time_ptr end;
    Renter_ptr renter;
    Thing_ptr thing;

public:
    Rent(Renter_ptr renter, Thing_ptr thing, Time_ptr begin);
    virtual ~Rent();
    std::string rentInfo(bool renterInfo=true);
    double getRentCost();
    void endRent();
    int getRentDuration();
    void extendFreeRental(Time_ptr time);
    const Renter_ptr &getRenter() const;
    const Thing_ptr &getThing() const;
    int getChargeDuration() const;
    std::string getId() const;
};




#endif //BIBLIOTEKA_RENT_H


