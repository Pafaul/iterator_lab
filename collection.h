#ifndef COLLECTION_H
#define COLLECTION_H

#include "objects.h"
#include <vector>

class Collection
{
protected:
    int length;
public:
    Collection() {};
    virtual int getLength() = 0;
    virtual int pushBack(AbstractVehicle* vehicle) = 0;
    virtual AbstractVehicle * getItem(int i) = 0;
};

class AircraftCollection : public Collection
{
protected:
    std::vector<AbstractVehicle*> items;
public:
    AircraftCollection() : Collection() {items = std::vector<AbstractVehicle*>(); length = 0; }
    int getLength() override { return length; }
    int pushBack(AbstractVehicle* vehicle) override {
        items.push_back(vehicle);
        length = items.size();
        return length;
    }
    AbstractVehicle * getItem(int i) override { if (i < this->length && i >= 0) return items[i]; }
};

#endif // COLLECTION_H
