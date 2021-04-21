//
// Created by student on 22.12.2019.
//
#include <boost/test/unit_test.hpp>
#include "Renter.h"
#include "ContactInfo.h"
#include "RenterException.h"

BOOST_AUTO_TEST_SUITE(ClassRenterCheck)
    BOOST_AUTO_TEST_CASE(ConstructorTest){
        Renter_ptr renter(new Renter("Andrzej", "Kowalski", "99234758212", Other));
        BOOST_CHECK_EQUAL(renter->getFirstName(), "Andrzej");
        BOOST_CHECK_EQUAL(renter->getLastName(), "Kowalski");
        BOOST_CHECK_EQUAL(renter->getId(), "99234758212");
        BOOST_CHECK_EQUAL(renter->getAll(false), "Andrzej Kowalski 99234758212 Other");
    }

    BOOST_AUTO_TEST_CASE(RenterTypesTest) {
        Renter_ptr renter(new Renter("Andrzej", "Kowalski", "99234758212", Other));
        BOOST_CHECK_EQUAL(renter->getMaxThings(), 3);
        BOOST_CHECK_EQUAL(renter->getFreeRentDuration(), 14);
        renter->setRenterType(Student);
        BOOST_CHECK_EQUAL(renter->getMaxThings(), 4);
        BOOST_CHECK_EQUAL(renter->getFreeRentDuration(), 21);
        renter->setRenterType(Professor);
        BOOST_CHECK_EQUAL(renter->getMaxThings(), 5);
        BOOST_CHECK_EQUAL(renter->getFreeRentDuration(), 28);
    }
    BOOST_AUTO_TEST_CASE(ContactInfoConstructorTest){
        ContactInfo_ptr info(new ContactInfo("123456789", "Skrzywana", "21/50"));
        BOOST_CHECK_EQUAL(info->getAll(), "123456789 Skrzywana 21/50");
    }

    BOOST_AUTO_TEST_CASE(ContactInfoInRenterTest){
        Renter_ptr renter(new Renter("Andrzej", "Kowalski", "99234758212", Other));
        BOOST_CHECK_EQUAL(renter->getContactInfoStr(), "This renter didn't input contact information");
        ContactInfo_ptr info(new ContactInfo("123456789", "Skrzywana", "21/50"));
        renter->setContactInfo(info);
        BOOST_CHECK_EQUAL(renter->getContactInfoStr(), "123456789 Skrzywana 21/50");
    }
BOOST_AUTO_TEST_SUITE_END()