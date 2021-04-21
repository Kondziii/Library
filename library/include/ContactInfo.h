//
// Created by student on 22.12.2019.
//

#ifndef BIBLIOTEKA_CONTACTINFO_H
#define BIBLIOTEKA_CONTACTINFO_H


#include <string>
#include <memory>

class ContactInfo {
    std::string phoneNumber;
    std::string street;
    std::string number;
public:
    ContactInfo(std::string phoneNumber, std::string street, std::string number);
    virtual ~ContactInfo();
    std::string getAll();
};
typedef std::shared_ptr<ContactInfo> ContactInfo_ptr;


#endif //BIBLIOTEKA_CONTACTINFO_H