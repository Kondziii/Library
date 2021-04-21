#include <iostream>
#include <Renter.h>
#include <Book.h>
#include <Movie.h>
#include <Rent.h>
#include <RentersRepository.h>
#include <ThingsRepository.h>
#include <RentsRepository.h>
#include <RentersManager.h>
#include <ThingsManager.h>
#include <RentsManager.h>

using namespace boost::posix_time;
using namespace boost::gregorian;
using namespace boost::local_time;
using namespace std;

int main() {
    Renter_ptr renter(new Renter("Andrzej", "Kowalski", "99234758212", Other));
    cout<<renter->getAll(false)<<endl;
    cout<<endl;

    ContactInfo_ptr info(new ContactInfo("123456789", "Skrzywana", "21/50"));
    renter->setContactInfo(info);
    cout<<info->getAll()<<endl;
    cout<<renter->getAll(false)<<endl;
    cout<<endl;

    Thing_ptr book(new Book("b123", "Witcher", 0.4, "Sapkowski", 2007));
    Thing_ptr movie1(new Movie("m123","Stupid and more stupid", 0.5));
    Thing_ptr movie2(new Movie("m123","Stupid and more stupid", 0.5, true));
    cout<<book->getInfo()<<endl;
    cout<<movie1->getInfo()<<endl;
    cout<<movie2->getInfo()<<endl;
    cout<<endl;

    Renter_ptr renter2(new Renter("Andrzej", "Kowalski", "99234758212", Other));
    Thing_ptr book2(new Book("b123", "Witcher", 0.4, "Sapkowski", 2007));
    ptime dt =ptime(date(2019, Dec, 1), hours(12));
    time_zone_ptr tz_cet(new posix_time_zone("CET"));
    Time_ptr begin(new local_date_time(dt, tz_cet));
    Time_ptr end(new local_date_time(local_sec_clock::local_time(tz_cet)));
    Rent_ptr rent1(new Rent(renter2, book2, begin));

    cout<<rent1->rentInfo()<<endl;
    cout<<endl;
    cout<<renter2->getAll()<<endl;

    rent1->endRent();
    cout<<rent1->rentInfo()<<endl;
    cout<<endl;

    RentersRepository *repository1 = new RentersRepository;
    Renter_ptr renter10(new Renter("Andrzej1", "Kowalski1", "99234758214", Other));
    Renter_ptr renter20(new Renter("Andrzej2", "Kowalski2", "99234758221", Student));
    Renter_ptr renter30(new Renter("Andrzej3", "Kowalski3", "99234758219", Professor));
    repository1->add(renter10);
    repository1->add(renter20);
    repository1->add(renter30);
    //cout<<repository1->getAll()<<endl;
    cout << *repository1 << endl;
    RentersManager *manager1 = new RentersManager(repository1);
    cout<<manager1->getAllRenterInfo()<<endl;
    delete manager1;

    ThingsRepository *repository2 =new ThingsRepository;
    Thing_ptr book11(new Book("book1", "title1", 0.5, "author1", 1990));
    Thing_ptr book22(new Book("book2", "title2", 0.5, "author2", 1990));
    repository2->add(book11);
    repository2->add(book22);
    Thing_ptr movie11(new Movie("movie1", "title1", 0.8));
    Thing_ptr movie22(new Movie("movie2", "title2", 0.8));
    repository2->add(movie11);
    repository2->add(movie22);
    //cout<<repository2->getAll()<<endl;
    cout<<*repository2<<endl;
    ThingsManager *manager2 = new ThingsManager(repository2);
    cout<<manager2->getAllThingInfo()<<endl;
    delete manager2;

    RentsRepository *repository3=new RentsRepository;
    Renter_ptr renter12(new Renter("Andrzej1", "Kowalski1", "99234758214", Other));
    Renter_ptr renter22(new Renter("Andrzej2", "Kowalski2", "99234758221", Student));
    Renter_ptr renter32(new Renter("Andrzej3", "Kowalski3", "99234758219", Professor));
    Thing_ptr book12(new Book("book1", "title1", 0.5, "author1", 1990));
    Thing_ptr book23(new Book("book2", "title2", 0.5, "author2", 1990));
    Thing_ptr movie12(new Movie("movie1", "title1", 0.8));
    Rent_ptr rent12(new Rent(renter12,book12,begin));
    Rent_ptr rent23(new Rent(renter22,book23,begin));
    Rent_ptr rent32(new Rent(renter32,movie12,begin));
    repository3->add(rent12);
    repository3->add(rent23);
    repository3->add(rent32);
    //cout<<repository3->getAll()<<endl;
    cout<<*repository3<<endl;
    RentsManager *manager3 = new RentsManager(repository3);
    cout<<manager3->getAllRentInfo()<<endl;
    delete manager3;

    return 0;
}