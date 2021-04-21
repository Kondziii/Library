//
// Created by student on 23.12.2019.
//

#ifndef BIBLIOTEKA_RENTEREXCEPTION_H
#define BIBLIOTEKA_RENTEREXCEPTION_H


#include <stdexcept>

class RenterException : public std::logic_error {
public:
    explicit RenterException(std::string n);
};


#endif //BIBLIOTEKA_RENTEREXCEPTION_H
