//
// Created by student on 27.12.2019.
//
#include <boost/test/unit_test.hpp>
#include <ThingsRepository.h>
#include <RentersRepository.h>
#include <Rent.h>
#include <RentsRepository.h>
#include "Book.h"
#include "Movie.h"
#include "Thing.h"

using namespace boost::posix_time;
using namespace boost::gregorian;
using namespace boost::local_time;

BOOST_AUTO_TEST_SUITE(ThingsRepositorySuiteCorrect)
    BOOST_AUTO_TEST_CASE(ThingsRepositoryCheck) {
        ThingsRepository *repository = new ThingsRepository;
        Thing_ptr book1(new Book("book1", "title1", 0.5, "author1", 1990));
        Thing_ptr book2(new Book("book2", "title2", 0.5, "author2", 1990));
        Thing_ptr book3(new Book("book3", "title3", 0.5, "author3", 1990));
        Thing_ptr book4(new Book("book4", "title4", 0.5, "author4", 1990));
        repository->add(book1);
        repository->add(book2);
        repository->add(book3);
        repository->add(book4);
        Thing_ptr movie1(new Movie("movie1", "title1", 0.8));
        Thing_ptr movie2(new Movie("movie2", "title2", 0.8));
        Thing_ptr movie3(new Movie("movie3", "title3", 0.8));
        Thing_ptr movie4(new Movie("movie4", "title4", 0.8));
        repository->add(movie1);
        repository->add(movie2);
        repository->add(movie3);
        repository->add(movie4);
        BOOST_CHECK_EQUAL(repository->getRepositorySize(), 8);
        BOOST_CHECK_EQUAL(repository->checkPresence(movie2), true);
        BOOST_CHECK_EQUAL(movie1->getBaseRentCharge(), 0.8);
        repository->changeCharge(movie1, 0.4);
        BOOST_CHECK_EQUAL(movie1->getBaseRentCharge(), 0.4);
        repository->remove(movie1);
        BOOST_CHECK_EQUAL(repository->getRepositorySize(), 7);
        BOOST_CHECK_EQUAL(repository->checkPresence(movie1), false);
        delete repository;
    }
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(RentersRepositorySuiteCorrect)
    BOOST_AUTO_TEST_CASE(RentersRepositoryCheck) {
        RentersRepository *repository = new RentersRepository;
        Renter_ptr renter1(new Renter("Andrzej1", "Kowalski1", "99234758214", Other));
        Renter_ptr renter2(new Renter("Andrzej2", "Kowalski2", "99234758221", Student));
        Renter_ptr renter3(new Renter("Andrzej3", "Kowalski3", "99234758219", Professor));
        BOOST_CHECK_EQUAL(repository->getRepositorySize(), 0);
        repository->add(renter1);
        repository->add(renter2);
        repository->add(renter3);
        BOOST_CHECK_EQUAL(repository->getRepositorySize(), 3);
        BOOST_CHECK_EQUAL(renter1->getRenterTypeName(), "Other");
        repository->changeRenterType(renter1, Student);
        BOOST_CHECK_EQUAL(renter1->getRenterTypeName(), "Student");
        BOOST_CHECK_EQUAL(repository->checkPresence(renter2), true);
        repository->remove(renter2);
        BOOST_CHECK_EQUAL(repository->checkPresence(renter2), false);
        BOOST_CHECK_EQUAL(repository->getRepositorySize(), 2);
        delete repository;
    }
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(RentsRepositorySuiteCorrect)
    BOOST_AUTO_TEST_CASE(RentsRepositoryCheck){
        Renter_ptr renter1(new Renter("Andrzej1", "Kowalski1", "99234758214", Other));
        Renter_ptr renter2(new Renter("Andrzej2", "Kowalski2", "99234758221", Student));
        Renter_ptr renter3(new Renter("Andrzej3", "Kowalski3", "99234758219", Professor));
        Thing_ptr book1(new Book("book1", "title1", 0.5, "author1", 1990));
        Thing_ptr book2(new Book("book2", "title2", 0.5, "author2", 1990));
        Thing_ptr movie1(new Movie("movie1", "title1", 0.8));
        ptime dt =ptime(date(2019, Dec, 1), hours(12));
        time_zone_ptr tz_cet(new posix_time_zone("CET"));
        Time_ptr begin(new local_date_time(dt, tz_cet));
        Rent_ptr rent1(new Rent(renter1,book1,begin));
        Rent_ptr rent2(new Rent(renter1,book2,begin));
        Rent_ptr rent3(new Rent(renter2,movie1,begin));
        RentsRepository *repository=new RentsRepository;
        BOOST_CHECK_EQUAL(repository->getRepositorySize(),0);
        repository->add(rent1);
        repository->add(rent2);
        repository->add(rent3);
        BOOST_CHECK_EQUAL(repository->getRepositorySize(),3);
        BOOST_CHECK_EQUAL(repository->checkPresence(rent1), true);
        BOOST_CHECK_EQUAL(repository->isRented(book1), true);
        BOOST_CHECK_EQUAL(repository->getRenterForRentedThing(book1), renter1);
        BOOST_CHECK_EQUAL(repository->findThingRental(book1), rent1);
        BOOST_CHECK_EQUAL(repository->getAllRenterRents(renter1).size(), 2);
        BOOST_CHECK_EQUAL(repository->getAllRenterRents(renter1)[0], rent1);
        repository->remove(rent1);
        BOOST_CHECK_EQUAL(repository->getRepositorySize(),2);
        BOOST_CHECK_EQUAL(repository->checkPresence(rent1), false);
        BOOST_CHECK_EQUAL(repository->isRented(book1), false);
        BOOST_CHECK_EQUAL(repository->getRenterForRentedThing(book1), nullptr);
        BOOST_CHECK_EQUAL(repository->findThingRental(book1), nullptr);
        BOOST_CHECK_EQUAL(repository->getAllRenterRents(renter1).size(), 1);
        BOOST_CHECK_EQUAL(repository->getAllRenterRents(renter1)[0], rent2);
        delete repository;
    }
BOOST_AUTO_TEST_SUITE_END()
