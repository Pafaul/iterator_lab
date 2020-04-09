#ifndef ITERATOR_H
#define ITERATOR_H

#include "sortingalgorythm.h"


class VehicleIterator
{
protected:
    std::string tag;
    std::string property;
    std::vector<int> filteredItems;
    std::vector<int> filterItems(Collection * c, std::string tag, std::string property);

public:
    VehicleIterator();
    VehicleIterator(Collection * c, std::string tag, std::string property) {};
    virtual TemplateVehicle* getNext() = 0;
    virtual bool hasMore() = 0;
    ~VehicleIterator() {};
};


class CircleVehicleIterator :  public VehicleIterator
{
protected:
    Collection * collection;
    int currentItem = -1;

public:
    CircleVehicleIterator(): VehicleIterator() {};
    CircleVehicleIterator(Collection * c, std::string tag, std::string property);
    TemplateVehicle * getNext() override;
    bool hasMore() override;
};


class OneDirectionIterator : public VehicleIterator
{
protected:
    Collection * collection;
    int currentItem = -1;
public:
    OneDirectionIterator(): VehicleIterator() {};
    OneDirectionIterator(Collection * c, std::string tag, std::string property);
    TemplateVehicle * getNext() override;
    bool hasMore() override;
};


class SortIterator : public VehicleIterator
{
protected:
    virtual void getSorted() = 0;
    SortingAlgorythm * sortingAlgorithm;
    bool reversed;
public:
    SortIterator() : VehicleIterator() {};
    SortIterator(Collection * c, std::string tag, std::string property) : VehicleIterator(c, tag, property) {};
    virtual TemplateVehicle * getNext() override = 0;
    virtual bool hasMore() override = 0;
    void setSortingAlgorithm(SortingAlgorythm * sortAlgorythm) { this->sortingAlgorithm = sortAlgorythm; };
    void reverse() {this->reversed = this->reversed ? false : true; };
};


class CircleSortIterator : public SortIterator
{
protected:
    virtual void getSorted() override;
    Collection * collection;
    unsigned long currentItem = -1;
    unsigned long collectionSize;
    std::vector<int> preSorted;
public:
    CircleSortIterator(): SortIterator() {};
    CircleSortIterator(Collection *c, std::string tag, std::string property);
    TemplateVehicle * getNext() override;
    bool hasMore() override;
};
class OneDirectionSortIterator : public SortIterator
{
protected:
    virtual void getSorted() override;
    Collection * collection;
    unsigned long currentItem = -1;
    unsigned long collectionSize;
    std::vector<int> preSorted;
public:
    OneDirectionSortIterator(): SortIterator() {};
    OneDirectionSortIterator(Collection *c, std::string tag, std::string property);
    TemplateVehicle * getNext() override;
    bool hasMore() override;
};

#endif // ITERATOR_H
