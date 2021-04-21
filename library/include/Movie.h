//
// Created by student on 23.12.2019.
//

#ifndef BIBLIOTEKA_MOVIE_H
#define BIBLIOTEKA_MOVIE_H


#include "Thing.h"

class Movie : public Thing{
    bool subtitles;

public:
    Movie(std::string id, std::string title, double baseRentCharge, bool subtitles=false);
    ~Movie() override;
    std::string getInfo() override;
    double getActualCharge() override;
};


#endif //BIBLIOTEKA_MOVIE_H
