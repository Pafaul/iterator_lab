#ifndef COLLECTION_H
#define COLLECTION_H

#include "vehicles.h"

class Collection
{
public:
    Collection() {};
    virtual int getLength() = 0;
    virtual int pushBack(TemplateVehicle* vehicle) = 0;
    virtual TemplateVehicle* getItem(int i) = 0;
};

class VehicleCollection : public Collection
{
protected:
    std::vector<TemplateVehicle*> items;
public:
    VehicleCollection();
    int getLength() override;
    int pushBack(TemplateVehicle* vehicle) override;
    TemplateVehicle * getItem(int i) override;
};

#endif // COLLECTION_H
