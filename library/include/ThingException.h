//
// Created by student on 23.12.2019.
//

#ifndef BIBLIOTEKA_THINGEXCEPTION_H
#define BIBLIOTEKA_THINGEXCEPTION_H


#include <stdexcept>

class ThingException : public std::logic_error {
public:
    ThingException(std::string n);
};


#endif //BIBLIOTEKA_THINGEXCEPTION_H
