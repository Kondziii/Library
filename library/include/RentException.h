//
// Created by student on 23.12.2019.
//

#ifndef BIBLIOTEKA_RENTEXCEPTION_H
#define BIBLIOTEKA_RENTEXCEPTION_H


#include <stdexcept>

class RentException : public std::logic_error {
public:
    RentException(std::string n);
};


#endif //BIBLIOTEKA_RENTEXCEPTION_H
