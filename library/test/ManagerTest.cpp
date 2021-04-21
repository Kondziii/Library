//
// Created by student on 27.12.2019.
//
#include <boost/test/unit_test.hpp>
#include <ThingsRepository.h>
#include <RentersRepository.h>
#include <Rent.h>
#include <RentsRepository.h>
#include <RentersManager.h>
#include <ThingsManager.h>
#include <RentsManager.h>
#include "Book.h"
#include "Movie.h"
#include "Thing.h"

using namespace boost::posix_time;
using namespace boost::gregorian;
using namespace boost::local_time;

BOOST_AUTO_TEST_SUITE(RentersManagerSuiteCorrect)
BOOST_AUTO_TEST_CASE(RentersManagerCheck) {
        RentersRepository *repository = new RentersRepository;
        Renter_ptr renter1(new Renter("Andrzej1", "Kowalski1", "99234758214", Other));
        Renter_ptr renter2(new Renter("Andrzej2", "Kowalski2", "99234758221", Student));
        Renter_ptr renter3(new Renter("Andrzej3", "Kowalski3", "99234758219", Professor));
        BOOST_CHECK_EQUAL(repository->getRepositorySize(), 0);
        RentersManager *manager = new RentersManager(repository);
        manager->addRenter(renter1);
        manager->addRenter(renter2);
        BOOST_CHECK_EQUAL(repository->getRepositorySize(), 2);
        BOOST_CHECK_EQUAL(repository->checkPresence(renter1), true);
        BOOST_CHECK_EQUAL(repository->checkPresence(renter2), true);
        BOOST_CHECK_EQUAL(renter1->getRenterTypeName(),"Other");
        manager->changeRenterType(renter1, Professor);
        BOOST_CHECK_EQUAL(renter1->getRenterTypeName(),"Professor");
        manager->removeRenter(renter1);
        BOOST_CHECK_EQUAL(repository->getRepositorySize(), 1);
        BOOST_CHECK_EQUAL(repository->checkPresence(renter1), false);
        BOOST_CHECK_EQUAL(repository->checkPresence(renter2), true);
        delete manager;
    }
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(ThingsManagerSuiteCorrect)
BOOST_AUTO_TEST_CASE(ThingsManagerCheck){
        ThingsRepository *repository = new ThingsRepository;
        Thing_ptr book1(new Book("book1", "title1", 0.5, "author1", 1990));
        Thing_ptr movie1(new Movie("movie1", "title1", 0.8));
        ThingsManager* manager=new ThingsManager(repository);
        manager->addThing(book1);
        manager->addThing(movie1);
        BOOST_CHECK_EQUAL(repository->getRepositorySize(), 2);
        BOOST_CHECK_EQUAL(repository->checkPresence(book1), true);
        BOOST_CHECK_EQUAL(repository->checkPresence(movie1), true);
        BOOST_CHECK_EQUAL(book1->getBaseRentCharge(), 0.5);
        manager->changeCharge(book1, 0.7);
        BOOST_CHECK_EQUAL(book1->getBaseRentCharge(), 0.7);
        manager->removeThing(book1);
        BOOST_CHECK_EQUAL(repository->getRepositorySize(), 1);
        BOOST_CHECK_EQUAL(repository->checkPresence(book1), false);
        BOOST_CHECK_EQUAL(repository->checkPresence(movie1), true);
        delete manager;
}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(RentsManagerSuiteCorrect)
BOOST_AUTO_TEST_CASE(RentsManagerCheck){
        Renter_ptr renter1(new Renter("Andrzej1", "Kowalski1", "99234758214", Other));
        Renter_ptr renter2(new Renter("Andrzej2", "Kowalski2", "99234758221", Student));
        Renter_ptr renter3(new Renter("Andrzej3", "Kowalski3", "99234758219", Professor));
        Thing_ptr book1(new Book("book1", "title1", 0.5, "author1", 1990));
        Thing_ptr book2(new Book("book2", "title2", 0.5, "author2", 1990));
        Thing_ptr movie1(new Movie("movie1", "title1", 0.8));
        ptime dt =ptime(date(2019, Dec, 1), hours(12));
        time_zone_ptr tz_cet(new posix_time_zone("CET"));
        Time_ptr begin(new local_date_time(dt, tz_cet));
        RentsRepository *repository=new RentsRepository;
        BOOST_CHECK_EQUAL(repository->getRepositorySize(),0);
        RentsManager* manager(new RentsManager(repository));
        manager->addRent(renter1, book1, begin);
        manager->addRent(renter2, book2, begin);
        manager->addRent(renter3, movie1, begin);
        BOOST_CHECK_EQUAL(repository->getRepositorySize(),3);
        Rent_ptr rent1=repository->findThingRental(book1);
        BOOST_CHECK_EQUAL(rent1->getRentCost(), 0);
        ptime dt2 =ptime(date(2019, Dec, 10));
        Time_ptr time(new boost::local_time::local_date_time(dt2, tz_cet));
        manager->extendRental(book1, time);
        manager->removeRent(book1);
        double price;
        if(rent1->getRentDuration()-2*renter1->getFreeRentDuration()<0) {
            price = 0;
        }
        else{
            price=(rent1->getRentDuration()-2*renter1->getFreeRentDuration())*0.4;
        }
        BOOST_CHECK_EQUAL(rent1->getRentCost(), price);
        BOOST_CHECK_EQUAL(repository->getRepositorySize(),2);
        BOOST_CHECK_EQUAL(manager->getAllRenterRents(renter2)[0]->getRentCost(), 0);
}
BOOST_AUTO_TEST_SUITE_END()
