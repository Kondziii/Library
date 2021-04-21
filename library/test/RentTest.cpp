//
// Created by student on 23.12.2019.
//
#include <boost/test/unit_test.hpp>
#include <Renter.h>
#include <boost/date_time/posix_time/ptime.hpp>
#include <boost/date_time/posix_time/posix_time_duration.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <Rent.h>
#include "Thing.h"
#include "Book.h"
#include "Movie.h"
#include "Rent.h"
using namespace boost::posix_time;
using namespace boost::gregorian;
using namespace boost::local_time;

double roundTwoAfterPoint(double figure){
    figure=figure*100;
    figure=(int)figure;
    figure=figure/100;
    return figure;
}

BOOST_AUTO_TEST_SUITE(RentCorrectSuite)

    BOOST_AUTO_TEST_CASE(RentConstructorTest){
        Renter_ptr renter(new Renter("Andrzej", "Kowalski", "99234758212", Other));
        Thing_ptr book(new Book("b123", "Witcher", 0.4, "Sapkowski", 2007));
        ptime dt =ptime(date(2019, Dec, 1), hours(12));
        time_zone_ptr tz_cet(new posix_time_zone("CET"));
        Time_ptr begin(new local_date_time(dt, tz_cet));
        Time_ptr end(new local_date_time(local_sec_clock::local_time(tz_cet)));
        Rent_ptr rent1(new Rent(renter, book, begin));
        BOOST_CHECK_EQUAL(rent1->getRenter(), renter);
        BOOST_CHECK_EQUAL(rent1->getThing(), book);
        BOOST_CHECK_EQUAL(rent1->getRentCost(), 0);
        BOOST_CHECK_EQUAL(rent1->getRentDuration(),0);
        rent1->endRent();
        double price=roundTwoAfterPoint(((end->date()-begin->date()).days()+1-14)*0.4);
        BOOST_CHECK_EQUAL(rent1->getRentCost(), price);
        BOOST_CHECK_EQUAL(rent1->getRentDuration(), (end->date()-begin->date()).days()+1);
    }

    BOOST_AUTO_TEST_CASE(RentPriceCheck){
        Renter_ptr renter(new Renter("Andrzej", "Kowalski", "99234758212", Other));
        Thing_ptr book(new Book("b123", "Witcher", 0.4, "Sapkowski", 2007));
        Thing_ptr movie(new Movie("m123","Stupid and more stupid", 0.5, true));
        ptime dt =ptime(date(2019, Dec, 1), hours(12));
        time_zone_ptr tz_cet(new posix_time_zone("CET"));
        Time_ptr begin(new boost::local_time::local_date_time(dt, tz_cet));
        Rent_ptr rent1(new Rent(renter, book, begin));
        Rent_ptr rent2(new Rent(renter, movie, begin));
        BOOST_CHECK_EQUAL(rent1->getRentCost(), 0);
        BOOST_CHECK_EQUAL(rent2->getRentCost(), 0);
        rent1->endRent();
        rent2->endRent();
        double price1=(rent1->getRentDuration()-renter->getFreeRentDuration())*0.4;
        price1=roundTwoAfterPoint(price1);
        double price2=(rent2->getRentDuration()-renter->getFreeRentDuration())*0.7;
        price2=roundTwoAfterPoint(price2);
        BOOST_CHECK_EQUAL(rent1->getRentCost(), price1);
        BOOST_CHECK_EQUAL(rent2->getRentCost(), price2);
    }

    BOOST_AUTO_TEST_CASE(CheckRentAndRenterRealtion){
        Renter_ptr renter(new Renter("Andrzej", "Kowalski", "99234758212", Other));
        Thing_ptr book(new Book("b123", "Witcher", 0.4, "Sapkowski", 2007));
        ptime dt =ptime(date(2019, Dec, 1), hours(12));
        time_zone_ptr tz_cet(new posix_time_zone("CET"));
        Time_ptr begin(new boost::local_time::local_date_time(dt, tz_cet));
        BOOST_CHECK_EQUAL(renter->getRents().size(), 0);
        Rent_ptr rent1(new Rent(renter, book, begin));
        BOOST_CHECK_EQUAL(renter->getRents().size(), 1);
        BOOST_CHECK_EQUAL(renter->getRents()[0]->getThing(), book);
        BOOST_CHECK_EQUAL(renter->getRents()[0]->getThing()->getTitle(),rent1->getThing()->getTitle());
        BOOST_CHECK_EQUAL(renter->getNumberOfPossibleRents(), 2);
        BOOST_CHECK_EQUAL(rent1->getRentDuration(), 0);
        rent1->endRent();
        BOOST_CHECK_EQUAL(renter->getRents().size(),0);
        BOOST_CHECK_EQUAL(renter->getNumberOfPossibleRents(), 3);
    }

    BOOST_AUTO_TEST_CASE(CheckExtensionOfRentFirstCase){  // dwa przedluzenia bez kary pomiedzy nimi
        Renter_ptr renter(new Renter("Andrzej", "Kowalski", "99234758212", Other));
        Thing_ptr book(new Book("b123", "Witcher", 0.4, "Sapkowski", 2007));
        ptime dt =ptime(date(2019, Nov, 17), hours(12));
        time_zone_ptr tz_cet(new posix_time_zone("CET"));
        Time_ptr begin(new boost::local_time::local_date_time(dt, tz_cet));
        Rent_ptr rent1(new Rent(renter, book, begin));
        BOOST_CHECK_EQUAL(rent1->getRentCost(), 0);
        ptime dt3 =ptime(date(2019, Nov, 30), hours(12));
        Time_ptr time3(new boost::local_time::local_date_time(dt3, tz_cet));
        rent1->extendFreeRental(time3);
        ptime dt2 =ptime(date(2019, Dec, 11), hours(12));
        Time_ptr time(new boost::local_time::local_date_time(dt2, tz_cet));
        rent1->extendFreeRental(time);
        rent1->endRent();
        double price;
        if(rent1->getRentDuration()-3*renter->getFreeRentDuration()<0) {
            price = 0;
        }
        else{
            price=(rent1->getRentDuration()-3*renter->getFreeRentDuration())*0.4;
        }
        price=roundTwoAfterPoint(price);
        BOOST_CHECK_EQUAL(rent1->getRentCost(), price);
    }

    BOOST_AUTO_TEST_CASE(CheckExtensionOfRentSecondCase){ // sprawdzenie ceny w przypadku kary pomiedzy przedluzeniem
        Renter_ptr renter(new Renter("Andrzej", "Kowalski", "99234758212", Other));
        Thing_ptr book(new Book("b123", "Witcher", 0.4, "Sapkowski", 2007));
        ptime dt =ptime(date(2019, Nov, 26));
        time_zone_ptr tz_cet(new posix_time_zone("CET"));
        Time_ptr begin(new boost::local_time::local_date_time(dt, tz_cet));
        Rent_ptr rent1(new Rent(renter, book, begin));
        BOOST_CHECK_EQUAL(rent1->getRentCost(), 0);
        ptime dt2 =ptime(date(2019, Dec, 10));
        Time_ptr time(new boost::local_time::local_date_time(dt2, tz_cet));
        rent1->extendFreeRental(time);
        rent1->endRent();
        double price1=roundTwoAfterPoint((rent1->getRentDuration()+rent1->getChargeDuration()-2*renter->getFreeRentDuration())*0.4);
        BOOST_CHECK_EQUAL(rent1->getRentCost(), price1);
    }

    BOOST_AUTO_TEST_CASE(CheckExtensionOfRentThirdCase){ //w momencie pisania testu sprawdzenie czy oplata wynosi 0 w przypadku terminowych przedluzen
        Renter_ptr renter(new Renter("Andrzej", "Kowalski", "99234758212", Other));
        Thing_ptr book(new Book("b123", "Witcher", 0.4, "Sapkowski", 2007));
        ptime dt =ptime(date(2019, Nov, 26));
        time_zone_ptr tz_cet(new posix_time_zone("CET"));
        Time_ptr begin(new boost::local_time::local_date_time(dt, tz_cet));
        Rent_ptr rent1(new Rent(renter, book, begin));
        BOOST_CHECK_EQUAL(rent1->getRentCost(), 0);
        ptime dt2 =ptime(date(2019, Dec, 8));
        Time_ptr time(new boost::local_time::local_date_time(dt2, tz_cet));
        rent1->extendFreeRental(time);
        rent1->endRent();
        double price=(rent1->getRentDuration()+rent1->getChargeDuration()-2*renter->getFreeRentDuration())*0.4;
        price=roundTwoAfterPoint(price);
        BOOST_CHECK_EQUAL(rent1->getRentCost(), price);
    }

    BOOST_AUTO_TEST_CASE(CheckExtensionOfRentFourthCase){ //zmiana typu klienta przy przedluzeniu
        Renter_ptr renter(new Renter("Andrzej", "Kowalski", "99234758212", Other));
        Thing_ptr book(new Book("b123", "Witcher", 0.4, "Sapkowski", 2007));
        ptime dt =ptime(date(2019, Nov, 15));
        time_zone_ptr tz_cet(new posix_time_zone("CET"));
        Time_ptr begin(new boost::local_time::local_date_time(dt, tz_cet));
        Rent_ptr rent1(new Rent(renter, book, begin));
        BOOST_CHECK_EQUAL(rent1->getRentCost(), 0);
        ptime dt2 =ptime(date(2019, Dec, 1));
        Time_ptr time(new boost::local_time::local_date_time(dt2, tz_cet));
        renter->setRenterType(Student);
        rent1->extendFreeRental(time);
        rent1->endRent();
        double price;
        if((rent1->getRentDuration()-(2*renter->getFreeRentDuration()-7))<0) {
            price = 0+rent1->getChargeDuration()*0.4;
        }
        else{
            price=(rent1->getRentDuration()+rent1->getChargeDuration()-(2*renter->getFreeRentDuration()-7))*0.4;
        }
        price=roundTwoAfterPoint(price);
        BOOST_CHECK_EQUAL(rent1->getRentCost(), price);
    }

    BOOST_AUTO_TEST_CASE(CheckExtensionOfRentFifthCase){ //zmiana typu klienta przy przedluzeniu
        Renter_ptr renter(new Renter("Andrzej", "Kowalski", "99234758212", Other));
        Thing_ptr book(new Book("b123", "Witcher", 0.4, "Sapkowski", 2007));
        ptime dt =ptime(date(2019, Nov, 15));
        time_zone_ptr tz_cet(new posix_time_zone("CET"));
        Time_ptr begin(new boost::local_time::local_date_time(dt, tz_cet));
        Rent_ptr rent1(new Rent(renter, book, begin));
        BOOST_CHECK_EQUAL(rent1->getRentCost(), 0);
        ptime dt2 =ptime(date(2019, Dec, 1));
        Time_ptr time(new boost::local_time::local_date_time(dt2, tz_cet));
        renter->setRenterType(Student);
        rent1->extendFreeRental(time);
        ptime dt3 =ptime(date(2019, Dec, 22));
        Time_ptr time2(new boost::local_time::local_date_time(dt3, tz_cet));
        renter->setRenterType(Other);
        rent1->extendFreeRental(time2);
        rent1->endRent();
        double price;
        if((rent1->getRentDuration()-(3*renter->getFreeRentDuration()+7))<0) {
            price = 0+rent1->getChargeDuration()*0.4;
        }
        else{
            price=(rent1->getRentDuration()+rent1->getChargeDuration()-(3*renter->getFreeRentDuration()+7))*0.4;
        }
        price=roundTwoAfterPoint(price);
        BOOST_CHECK_EQUAL(rent1->getRentCost(), price);
    }

    BOOST_AUTO_TEST_CASE(CheckExtensionOfRentSixthCase){ //podwojna zmiana typu klienta przy przedluzeniu
        Renter_ptr renter(new Renter("Andrzej", "Kowalski", "99234758212", Other));
        Thing_ptr book(new Book("b123", "Witcher", 0.4, "Sapkowski", 2007));
        ptime dt =ptime(date(2019, Nov, 1));
        time_zone_ptr tz_cet(new posix_time_zone("CET"));
        Time_ptr begin(new boost::local_time::local_date_time(dt, tz_cet));
        Rent_ptr rent1(new Rent(renter, book, begin));
        BOOST_CHECK_EQUAL(rent1->getRentCost(), 0);
        ptime dt3 =ptime(date(2019, Nov, 16));
        Time_ptr time3(new boost::local_time::local_date_time(dt3, tz_cet));
        renter->setRenterType(Student);
        rent1->extendFreeRental(time3);
        ptime dt2 =ptime(date(2019, Dec, 11));
        Time_ptr time(new boost::local_time::local_date_time(dt2, tz_cet));
        renter->setRenterType(Professor);
        rent1->extendFreeRental(time);
        rent1->endRent();

        double price;
        if((rent1->getRentDuration()-(3*renter->getFreeRentDuration()-21))<0) {
            price = 0+rent1->getChargeDuration()*0.4;
        }
        else{
            price=(rent1->getRentDuration()+rent1->getChargeDuration()-(3*renter->getFreeRentDuration()-21))*0.4;
        }
        price=roundTwoAfterPoint(price);
        BOOST_CHECK_EQUAL(rent1->getRentCost(), price);
    }
BOOST_AUTO_TEST_SUITE_END()