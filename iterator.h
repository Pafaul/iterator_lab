#ifndef ITERATOR_H
#define ITERATOR_H

#include "collection.h"

class AbstractVehicleIterator
{    
public:
    AbstractVehicleIterator() {};
    AbstractVehicleIterator(Collection * c) {};
    virtual AbstractVehicle * getNext() = 0;
    virtual bool hasMore() = 0;
};

class OneDirectionalIterator : public AbstractVehicleIterator
{
protected:
    Collection * collection;
    int currentItem = -1;
public:
    OneDirectionalIterator() : AbstractVehicleIterator() {};
    OneDirectionalIterator(Collection * c) : AbstractVehicleIterator(c) {
        this->collection = c;
    }
    AbstractVehicle * getNext() override {
        currentItem += 1;
        if (this->hasMore()) {
            return collection->getItem(currentItem);
        } else {
            return collection->getItem(collection->getLength()-1);
        }
    };

    bool hasMore() override{
        return currentItem < collection->getLength();
    }
};

class CircleVehicleIterator :  public AbstractVehicleIterator
{
protected:
    Collection * collection;
    int currentItem = -1;
public:
    CircleVehicleIterator() : AbstractVehicleIterator() {};
    CircleVehicleIterator(Collection * c) : AbstractVehicleIterator(c) {
        this->collection = c;
    }
    AbstractVehicle * getNext() override {
        currentItem += 1;
        if (this->hasMore()) {
            return collection->getItem(currentItem);
        } else {
            currentItem = 0;
            return collection->getItem(currentItem);
        }
    };

    bool hasMore() override{
        return currentItem < collection->getLength();
    }
};



#endif // ITERATOR_H
