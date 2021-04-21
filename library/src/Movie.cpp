//
// Created by student on 23.12.2019.
//

#include <sstream>
#include "Movie.h"

Movie::Movie(std::string id, std::string title, double baseRentCharge, bool subtitles)
        :Thing(id, title, baseRentCharge), subtitles(subtitles)
{
}

std::string Movie::getInfo() {
    std::stringstream sout;
    sout<<Thing::getInfo()<<getActualCharge();
    if(subtitles){
        sout<<" available subtitles";
    }
    else{
        sout<<" unavailable subtitles";
    }
    return sout.str();
}

double Movie::getActualCharge() {
    double additionalCharge=0;
    if(subtitles){
        additionalCharge=0.2;
    }
    return additionalCharge+Thing::getActualCharge();
}

Movie::~Movie() {

}