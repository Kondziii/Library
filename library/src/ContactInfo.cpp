//
// Created by student on 22.12.2019.
//

#include <sstream>
#include <RenterException.h>
#include "ContactInfo.h"

ContactInfo::ContactInfo(std::string phoneNumber, std::string street, std::string number)
        : phoneNumber(phoneNumber), street(street), number(number)
{
    if(phoneNumber.size()!=9){
        throw RenterException("Inputed phone number is for sure incorrect");
    }
    if(street.size()<2){
        throw RenterException("Inputed street is incorrect");
    }
    if(number.size()==0){
        throw RenterException("Inputed number of home is incorrect");
    }
}

std::string ContactInfo::getAll() {
    std::stringstream sout;
    sout<<phoneNumber<<" "<<street<<" "<<number;
    return sout.str();
}

ContactInfo::~ContactInfo() {
}

