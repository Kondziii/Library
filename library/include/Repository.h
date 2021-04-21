//
// Created by student on 27.12.2019.
//

#ifndef BIBLIOTEKA_REPOSITORY_H
#define BIBLIOTEKA_REPOSITORY_H

#include <vector>
#include <fstream>
#include <string>
#include <boost/shared_ptr.hpp>

template <class T>

class Repository {
protected:
    std::vector<T> elements;

public:
    virtual void add(T element);
    virtual void remove(T element);
    virtual std::string getAll()=0;
    virtual bool checkPresence(T element);
    virtual int getRepositorySize();
    virtual ~Repository();
    virtual const std::vector<T> &getElements() const;

};

template<class T>
void Repository<T>::add(T element) {
    elements.push_back(element);
}

template<class T>
void Repository<T>::remove(T element) {
    for(auto i=elements.begin(); i!=elements.end(); ++i){
        if(*i==element){
            elements.erase(i);
            return;
        }
    }
}

template<class T>
bool Repository<T>::checkPresence(T element) {
    for(auto it: elements){
        if(it->getId()==element->getId()){
            return true;
        }
    }
    return false;
}

template<class T>
int Repository<T>::getRepositorySize() {
    return elements.size();
}

template<class T>
Repository<T>::~Repository() {
}

template<class T>
const std::vector<T> &Repository<T>::getElements() const {
    return elements;
}



#endif //BIBLIOTEKA_REPOSITORY_H
