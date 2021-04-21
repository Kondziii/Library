//
// Created by student on 22.12.2019.
//

#include <sstream>
#include <Student.h>
#include <Professor.h>
#include <RenterException.h>
#include "Renter.h"
#include "Rent.h"

Renter::Renter(std::string firstName, std::string lastName, std::string personalID, type renterType, ContactInfo_ptr contactInfo)
        : firstName(firstName), lastName(lastName), personalID(personalID), contactInfo(contactInfo)
{
    if(firstName.size()==0){
        throw RenterException("Incorrect first name");
    }
    if(lastName.size()==0){
        throw RenterException("Incorrect last name");
    }
    if(personalID.size()!=11){
        throw RenterException("Incorrect Id");
    }
    setRenterType(renterType);
}

const std::string &Renter::getFirstName() const {
    return firstName;
}

const std::string &Renter::getLastName() const {
    return lastName;
}

const std::string &Renter::getId() const {
    return personalID;
}

std::string Renter::getAll(bool rentInfo) {
    std::stringstream sout;
    sout<<firstName<<" "<<lastName<<" "<<personalID<<" "<<renterType->getTypeName();
    if(contactInfo!= nullptr){
        sout<<" "<<contactInfo->getAll();
    }
    if(rentInfo){
        sout<<"\n";
        for(auto it: rents){
            sout<<it->rentInfo(false)<<"\n";
        }
    }
    return sout.str();
}

int Renter::getMaxThings() {
    return renterType->getMaxThings();
}

int Renter::getFreeRentDuration() {
    return renterType->getFreeRentDuration();
}

Renter::~Renter() {
}

void Renter::setRenterType(type type) {
    switch(type){
        case Other:
            renterType=RenterTypes_ptr(new class Other());
            break;
        case Student:
            renterType=RenterTypes_ptr(new class Student());
            break;
        case Professor:
            renterType=RenterTypes_ptr(new class Professor());
            break;
    }
}

std::string  Renter::getContactInfoStr() const {
    if(contactInfo!= nullptr){
        return contactInfo->getAll();
    }
    return "This renter didn't input contact information";
}

void Renter::setContactInfo(ContactInfo_ptr contactInfo) {
    this->contactInfo=contactInfo;
}

void Renter::addRent(Rent *rent) {
    if(rents.size()<=this->getMaxThings()){
        rents.push_back(rent);
    }
    else throw RenterException("This renter actually can't have more rents");
}

void Renter::endRent(Rent *rent) {
    for(auto i=rents.begin(); i!=rents.end(); i++){
        if(*i==rent){
            rents.erase(i);
            return;
        }
    }
    throw RenterException("Renter haven't had this rental");
}

std::string Renter::getRenterTypeName() const{
    return renterType->getTypeName();
}

std::vector<Rent *> Renter::getRents() {
    return rents;
}

int Renter::getNumberOfPossibleRents() {
    return this->getMaxThings()-rents.size();
}



