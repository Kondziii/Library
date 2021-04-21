//
// Created by student on 23.12.2019.
//
#include <boost/test/unit_test.hpp>
#include "Thing.h"
#include "Book.h"
#include "Movie.h"


BOOST_AUTO_TEST_SUITE(ThingClassTest)
    BOOST_AUTO_TEST_CASE(BookConstructorTest){
        Thing_ptr book(new Book("b123", "Witcher", 0.4, "Sapkowski", 2007));
        BOOST_CHECK_EQUAL(book->getInfo(), "b123 Witcher Sapkowski 2007 0.4");
    }

    BOOST_AUTO_TEST_CASE(BookChargeCheck){
        Thing_ptr book(new Book("b123", "Witcher", 0.4, "Sapkowski", 1986));
        BOOST_CHECK_EQUAL(book->getActualCharge(), 0.54);
        Thing_ptr book2(new Book("b123", "Witcher", 0.4, "Sapkowski", 1970));
        BOOST_CHECK_EQUAL(book2->getActualCharge(), 0.7);
        Thing_ptr book3(new Book("b123", "Witcher", 0.4, "Sapkowski", 2000));
        BOOST_CHECK_EQUAL(book3->getActualCharge(), 0.4);
        Thing_ptr book4(new Book("b123", "Witcher", 0.4, "Sapkowski", 1990));
        BOOST_CHECK_EQUAL(book4->getActualCharge(), 0.5);
    }

    BOOST_AUTO_TEST_CASE(MovieConstructorTest){
        Thing_ptr movie(new Movie("m123","Stupid and more stupid", 0.5));
        BOOST_CHECK_EQUAL(movie->getInfo(), "m123 Stupid and more stupid 0.5 unavailable subtitles");
    }

    BOOST_AUTO_TEST_CASE(MovieChargeTest){
        Thing_ptr movie(new Movie("m123","Stupid and more stupid", 0.5));
        BOOST_CHECK_EQUAL(movie->getActualCharge(), 0.5);
        Thing_ptr movie2(new Movie("m123","Stupid and more stupid", 0.5, true));
        BOOST_CHECK_EQUAL(movie2->getActualCharge(), 0.7);
    }

BOOST_AUTO_TEST_SUITE_END()