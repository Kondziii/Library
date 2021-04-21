//
// Created by student on 22.12.2019.
//

#ifndef BIBLIOTEKA_RENTER_H
#define BIBLIOTEKA_RENTER_H


#include <string>
#include <memory>
#include <vector>
#include "ContactInfo.h"
#include "RenterTypes.h"
#include "Other.h"
#include "RenterException.h"
class Rent;
class Renter;
typedef std::shared_ptr<Renter> Renter_ptr;
enum type{
    Other, Student, Professor
};

class Renter {
    std::string firstName;
    std::string lastName;
    std::string personalID;
    ContactInfo_ptr contactInfo;
    RenterTypes_ptr renterType;
    std::vector<Rent*> rents;

public:
    Renter(std::string firstName, std::string lastName, std::string personalID, type renterType=Other, ContactInfo_ptr contactInfo=nullptr);
    virtual ~Renter();
    int getMaxThings();
    int getFreeRentDuration();
    std::string getAll(bool rentInfo=true);
    std::string getContactInfoStr() const;
    void addRent(Rent* rent);
    void endRent(Rent* rent);
    void setRenterType(type type);
    std::string getRenterTypeName() const;
    void setContactInfo(ContactInfo_ptr contactInfo);
    int getNumberOfPossibleRents();
    std::vector<Rent*> getRents();
    const std::string &getFirstName() const;
    const std::string &getLastName() const;
    const std::string &getId() const;
};

#endif //BIBLIOTEKA_RENTER_H


