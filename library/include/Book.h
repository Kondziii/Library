//
// Created by student on 23.12.2019.
//

#ifndef BIBLIOTEKA_BOOK_H
#define BIBLIOTEKA_BOOK_H

#include "Thing.h"


class Book : public Thing{
    std::string author;
    int releaseYear;

public:
    Book(std::string id, std::string title, double baseRentCharge, std::string author, int releaseYear);
    ~Book() override;
    std::string getInfo() override;
    double getActualCharge() override;
};


#endif //BIBLIOTEKA_BOOK_H

