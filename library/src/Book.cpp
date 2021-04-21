//
// Created by student on 23.12.2019.
//

#include <sstream>
#include <ThingException.h>
#include "Book.h"

Book::~Book() {

}

Book::Book(std::string id, std::string title, double baseRentCharge, std::string author, int releaseYear)
        : Thing(id,title,baseRentCharge), author(author), releaseYear(releaseYear)
{
    if(author.size()==0){
        throw ThingException("Incorrect author");
    }
    if(releaseYear<1800 || releaseYear>2020){
        throw ThingException("Incorect release date");
    }
}

std::string Book::getInfo() {
    std::stringstream sout;
    sout<<Thing::getInfo()<<author<<" "<<releaseYear<<" "<<getActualCharge();
    return sout.str();
}

double Book::getActualCharge() {
    double additionalCharge=0;
    if(releaseYear<1980){
        additionalCharge=0.3;
    }
    else if(releaseYear>=1980 && releaseYear<2000){
        additionalCharge=(double)((2000-releaseYear))/100;
    }
    return additionalCharge+Thing::getActualCharge();
}

