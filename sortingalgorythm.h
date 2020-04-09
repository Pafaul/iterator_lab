#ifndef SORTINGALGORYTHM_H
#define SORTINGALGORYTHM_H
#include "collection.h"
#include <algorithm>

class SortingAlgorythm
{
public:
    SortingAlgorythm() {};
    virtual std::vector<int> sort(Collection* c, std::vector<int> tagVehicles, std::string property, bool reverse) = 0;
};

class BubbleSort : public SortingAlgorythm
{
public:
    BubbleSort() : SortingAlgorythm() {};
    virtual std::vector<int> sort(Collection* c, std::vector<int> tagVehicles, std::string property, bool reverse) override;
};

class SelectionSort : public SortingAlgorythm
{
public:
    SelectionSort() : SortingAlgorythm() {};
    virtual std::vector<int> sort(Collection* c, std::vector<int> tagVehicles, std::string property, bool reverse) override;
};

class InsertionSort : public SortingAlgorythm
{
public:
    InsertionSort() : SortingAlgorythm() {};
    virtual std::vector<int> sort(Collection* c, std::vector<int> tagVehicles, std::string property, bool reverse) override;
};

#endif // SORTINGALGORYTHM_H
