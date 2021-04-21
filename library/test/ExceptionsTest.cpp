//
// Created by student on 23.12.2019.
//
#include <boost/test/unit_test.hpp>
#include <boost/date_time/local_time/local_date_time.hpp>
#include <boost/date_time/local_time/local_time.hpp>
#include <ThingsRepository.h>
#include <RentersRepository.h>
#include <RentersManager.h>
#include <ThingsManager.h>
#include <RentsRepository.h>
#include <RentsManager.h>
#include "Rent.h"
#include "Renter.h"
#include "ContactInfo.h"
#include "Thing.h"
#include "Book.h"
#include "Movie.h"
using namespace boost::posix_time;
using namespace boost::gregorian;
using namespace boost::local_time;

BOOST_AUTO_TEST_SUITE(ContactInfoExceptions)
    BOOST_AUTO_TEST_CASE(PhoneException){
        BOOST_CHECK_THROW(ContactInfo_ptr info(new ContactInfo("1234567", "Skrzywana", "21/50")), RenterException);
    }

    BOOST_AUTO_TEST_CASE(StreetException){
        BOOST_CHECK_THROW(ContactInfo_ptr info(new ContactInfo("123456789", "S", "21/50")), RenterException);
    }

    BOOST_AUTO_TEST_CASE(NumberException){
        BOOST_CHECK_THROW(ContactInfo_ptr info(new ContactInfo("123456789", "Skrzywana", "")), RenterException);
    }

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(RenterExceptions)
    BOOST_AUTO_TEST_CASE(FirstNameException){
        BOOST_CHECK_THROW(Renter_ptr renter(new Renter("", "Kowalski", "99234758212", Other)), RenterException);
    }

    BOOST_AUTO_TEST_CASE(LastNameException){
        BOOST_CHECK_THROW(Renter_ptr renter(new Renter("Andrzej", "", "99234758212", Other)), RenterException);
    }

    BOOST_AUTO_TEST_CASE(NumberException){
        BOOST_CHECK_THROW(Renter_ptr renter(new Renter("Andrzej", "Kowalski", "9923", Other)), RenterException);
    }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(ThingExceptions)
    BOOST_AUTO_TEST_CASE(IdException){
        BOOST_CHECK_THROW(Thing_ptr book(new Book("", "Witcher", 0.4, "Sapkowski", 2007)), ThingException);
    }

    BOOST_AUTO_TEST_CASE(TitleException){
        BOOST_CHECK_THROW(Thing_ptr book(new Book("b123", "", 0.4, "Sapkowski", 2007)), ThingException);
    }

    BOOST_AUTO_TEST_CASE(ChargeException){
        BOOST_CHECK_THROW(Thing_ptr book(new Book("b123", "Witcher", -0.2, "Sapkowski", 2007)), ThingException);
    }

    BOOST_AUTO_TEST_CASE(AuthorException){
        BOOST_CHECK_THROW(Thing_ptr book(new Book("b123", "Witcher", 0.4, "", 2007)), ThingException);
    }

    BOOST_AUTO_TEST_CASE(RleaseYearException){
        BOOST_CHECK_THROW(Thing_ptr book(new Book("b123", "Witcher", 0.4, "Sapkowski", -2000)),ThingException);
        BOOST_CHECK_THROW(Thing_ptr book(new Book("b123", "Witcher", 0.4, "Sapkowski", 2021)),ThingException);
    }
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(RentExceptions)
    BOOST_AUTO_TEST_CASE(ThingExceptionTest){
        Renter_ptr renter(new Renter("Andrzej", "Kowalski", "99234758212", Other));
        ptime dt =ptime(date(2019, Nov, 26));
        time_zone_ptr tz_cet(new posix_time_zone("CET"));
        Time_ptr begin(new boost::local_time::local_date_time(dt, tz_cet));
        BOOST_CHECK_THROW(Rent_ptr rent1(new Rent(renter, nullptr, begin)), RentException);
    }

    BOOST_AUTO_TEST_CASE(RenterExceptionTest){
        Thing_ptr book(new Book("b123", "Witcher", 0.4, "Sapkowski", 2007));
        ptime dt =ptime(date(2019, Nov, 26));
        time_zone_ptr tz_cet(new posix_time_zone("CET"));
        Time_ptr begin(new boost::local_time::local_date_time(dt, tz_cet));
        BOOST_CHECK_THROW(Rent_ptr rent1(new Rent(nullptr, book, begin)), RentException);
    }

    BOOST_AUTO_TEST_CASE(DateExceptionTest){
        Renter_ptr renter(new Renter("Andrzej", "Kowalski", "99234758212", Other));
        Thing_ptr book(new Book("b123", "Witcher", 0.4, "Sapkowski", 2007));
        ptime dt =ptime(date(2069, Nov, 26));
        time_zone_ptr tz_cet(new posix_time_zone("CET"));
        Time_ptr begin(new boost::local_time::local_date_time(dt, tz_cet));
        Rent_ptr rent1(new Rent(renter, book, begin));
        BOOST_CHECK_THROW(rent1->endRent(), RentException);
    }

    BOOST_AUTO_TEST_CASE(ExtendDateExceptionCase1){
        Renter_ptr renter(new Renter("Andrzej", "Kowalski", "99234758212", Other));
        Thing_ptr book(new Book("b123", "Witcher", 0.4, "Sapkowski", 2007));
        ptime dt =ptime(date(2019, Nov, 26));
        time_zone_ptr tz_cet(new posix_time_zone("CET"));
        Time_ptr begin(new boost::local_time::local_date_time(dt, tz_cet));
        Rent_ptr rent1(new Rent(renter, book, begin));
        ptime dt2 =ptime(date(2019, Nov, 24));
        Time_ptr time(new boost::local_time::local_date_time(dt2, tz_cet));
        BOOST_CHECK_THROW(rent1->extendFreeRental(time), RentException);
    }

    BOOST_AUTO_TEST_CASE(ExtendDateExceptionCase2){
        Renter_ptr renter(new Renter("Andrzej", "Kowalski", "99234758212", Other));
        Thing_ptr book(new Book("b123", "Witcher", 0.4, "Sapkowski", 2007));
        ptime dt =ptime(date(2019, Dec, 1));
        time_zone_ptr tz_cet(new posix_time_zone("CET"));
        Time_ptr begin(new boost::local_time::local_date_time(dt, tz_cet));
        Rent_ptr rent1(new Rent(renter, book, begin));
        ptime dt2 =ptime(date(2019, Dec, 8));
        Time_ptr time(new boost::local_time::local_date_time(dt2, tz_cet));
        BOOST_CHECK_THROW(rent1->extendFreeRental(time), RentException);

    }
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(RepositoryExceptions)
    BOOST_AUTO_TEST_CASE(ThingsRepositoryException){
        ThingsRepository *repository=new ThingsRepository;
        Thing_ptr book1(new Book("book1", "title1", 0.5, "author1", 1990));
        Thing_ptr book2(new Book("book2", "title2", 0.5, "author2", 1990));
        Thing_ptr book3(new Book("book3", "title3", 0.5, "author3", 1990));
        Thing_ptr book4(new Book("book4", "title4", 0.5, "author4", 1990));
        repository->add(book1);
        repository->add(book2);
        repository->add(book3);
        BOOST_CHECK_THROW(repository->changeCharge(book4,0.7), ThingException);
        delete repository;
    }

    BOOST_AUTO_TEST_CASE(RentersRepositoryException){
        RentersRepository *repository=new RentersRepository;
        Renter_ptr renter1(new Renter("Andrzej1", "Kowalski1", "99234758214", Other));
        Renter_ptr renter2(new Renter("Andrzej2", "Kowalski2", "99234758221", Student));
        Renter_ptr renter3(new Renter("Andrzej3", "Kowalski3", "99234758219", Professor));
        repository->add(renter1);
        repository->add(renter2);
        BOOST_CHECK_THROW(repository->changeRenterType(renter3, Student), RenterException);
        delete repository;
    }
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(ManagerExceptions)
    BOOST_AUTO_TEST_CASE(AddRenterWhichAlreadyIsInrepository){
        RentersRepository *repository = new RentersRepository;
        Renter_ptr renter1(new Renter("Andrzej1", "Kowalski1", "99234758214", Other));
        Renter_ptr renter2(new Renter("Andrzej2", "Kowalski2", "99234758221", Student));
        BOOST_CHECK_EQUAL(repository->getRepositorySize(), 0);
        RentersManager *manager = new RentersManager(repository);
        manager->addRenter(renter1);
        manager->addRenter(renter2);
        BOOST_CHECK_THROW(manager->addRenter(renter1), RenterException);
        delete manager;
    }

    BOOST_AUTO_TEST_CASE(RemoveRenterWhichAlreadyHasBeenRmeovedFromInrepository){
        RentersRepository *repository = new RentersRepository;
        Renter_ptr renter1(new Renter("Andrzej1", "Kowalski1", "99234758214", Other));
        Renter_ptr renter2(new Renter("Andrzej2", "Kowalski2", "99234758221", Student));
        BOOST_CHECK_EQUAL(repository->getRepositorySize(), 0);
        RentersManager *manager = new RentersManager(repository);
        manager->addRenter(renter1);
        manager->addRenter(renter2);
        manager->removeRenter(renter1);
        BOOST_CHECK_THROW(manager->removeRenter(renter1), RenterException);
        delete manager;
    }

    BOOST_AUTO_TEST_CASE(AddThingWhichAlreadyIsInrepository) {
        ThingsRepository *repository = new ThingsRepository;
        Thing_ptr book1(new Book("book1", "title1", 0.5, "author1", 1990));
        Thing_ptr movie1(new Movie("movie1", "title1", 0.8));
        BOOST_CHECK_EQUAL(repository->getRepositorySize(), 0);
        ThingsManager *manager = new ThingsManager(repository);
        manager->addThing(book1);
        manager->addThing(movie1);
        BOOST_CHECK_THROW(manager->addThing(book1), ThingException);
        delete manager;
    }

    BOOST_AUTO_TEST_CASE(RemoveThingWhichAlreadyHasBeenRmeovedFromInrepository) {
        ThingsRepository *repository = new ThingsRepository;
        Thing_ptr book1(new Book("book1", "title1", 0.5, "author1", 1990));
        Thing_ptr movie1(new Movie("movie1", "title1", 0.8));
        BOOST_CHECK_EQUAL(repository->getRepositorySize(), 0);
        ThingsManager *manager = new ThingsManager(repository);
        manager->addThing(book1);
        manager->addThing(movie1);
        manager->removeThing(book1);
        BOOST_CHECK_THROW(manager->removeThing(book1), ThingException);
        delete manager;
    }

    BOOST_AUTO_TEST_CASE(TryingToRentThingWhichIsRented) {
        Renter_ptr renter1(new Renter("Andrzej1", "Kowalski1", "99234758214", Other));
        Renter_ptr renter2(new Renter("Andrzej2", "Kowalski2", "99234758221", Student));
        Thing_ptr book1(new Book("book1", "title1", 0.5, "author1", 1990));
        ptime dt = ptime(date(2019, Dec, 1), hours(12));
        time_zone_ptr tz_cet(new posix_time_zone("CET"));
        Time_ptr begin(new local_date_time(dt, tz_cet));
        RentsRepository *repository = new RentsRepository;
        BOOST_CHECK_EQUAL(repository->getRepositorySize(), 0);
        RentsManager *manager(new RentsManager(repository));
        manager->addRent(renter1, book1, begin);
        BOOST_CHECK_THROW(manager->addRent(renter2, book1, begin), RentException);
        delete manager;
    }

    BOOST_AUTO_TEST_CASE(TryingToRentThingButRenterLimitIsUsed) {
        Renter_ptr renter1(new Renter("Andrzej1", "Kowalski1", "99234758214", Other));
        BOOST_CHECK_EQUAL(renter1->getMaxThings(), 3);
        Thing_ptr book1(new Book("book1", "title1", 0.5, "author1", 1990));
        Thing_ptr book2(new Book("book2", "title2", 0.5, "author2", 1990));
        Thing_ptr movie1(new Movie("movie1", "title1", 0.8));
        Thing_ptr movie2(new Movie("movie2", "title2", 0.8));
        ptime dt = ptime(date(2019, Dec, 1), hours(12));
        time_zone_ptr tz_cet(new posix_time_zone("CET"));
        Time_ptr begin(new local_date_time(dt, tz_cet));
        RentsRepository *repository = new RentsRepository;
        BOOST_CHECK_EQUAL(repository->getRepositorySize(), 0);
        RentsManager *manager(new RentsManager(repository));
        manager->addRent(renter1, book1, begin);
        manager->addRent(renter1, book2, begin);
        manager->addRent(renter1, movie1, begin);
        BOOST_CHECK_THROW(manager->addRent(renter1, movie2, begin), RentException);
        delete manager;
    }

    BOOST_AUTO_TEST_CASE(TryingToRemoveRentwhichHasBeenBeforeEnded) {
        Renter_ptr renter1(new Renter("Andrzej1", "Kowalski1", "99234758214", Other));
        Renter_ptr renter2(new Renter("Andrzej2", "Kowalski2", "99234758221", Student));
        Thing_ptr book1(new Book("book1", "title1", 0.5, "author1", 1990));
        ptime dt = ptime(date(2019, Dec, 1), hours(12));
        time_zone_ptr tz_cet(new posix_time_zone("CET"));
        Time_ptr begin(new local_date_time(dt, tz_cet));
        RentsRepository *repository = new RentsRepository;
        BOOST_CHECK_EQUAL(repository->getRepositorySize(), 0);
        RentsManager *manager(new RentsManager(repository));
        manager->addRent(renter1, book1, begin);
        manager->removeRent(book1);
        BOOST_CHECK_THROW(manager->removeRent(book1), RentException);
        delete manager;
    }
BOOST_AUTO_TEST_SUITE_END()