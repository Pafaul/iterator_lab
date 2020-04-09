#include "iterator.h"

/** Нахождение всех элементов, которые удовлетворяют заданному тэгу и имеют заданную характеристику средства передвижения
 * @brief VehicleIterator::filterItems
 * @param c
 * @param tag
 * @param property
 * @return
 */
std::vector<int> VehicleIterator::filterItems(Collection *c, std::string tag, std::string property) {
    std::vector<int> tagVehicles = std::vector<int>();
    if (tag == ""){
        for (int i = 0; i < c->getLength(); i++)
            tagVehicles.push_back(i);
    } else {
        std::vector<std::string> tags, properties;
        for (int i = 0; i < c->getLength(); i++){
            tags = c->getItem(i)->getTags();
            properties = c->getItem(i)->getAvailablePropertiesNames();
            if (std::find(tags.begin(), tags.end(), tag) != tags.end() &&
                    std::find(properties.begin(), properties.end(), property) != properties.end())
                tagVehicles.push_back(i);
        }
    }
    return tagVehicles;
}


/** Конструктор цикличного итератора
 * @brief CircleVehicleIterator::CircleVehicleIterator
 * @param c
 * @param tag
 * @param property
 */
CircleVehicleIterator::CircleVehicleIterator(Collection *c, std::string tag, std::string property) : VehicleIterator(c, tag, property) {
    this->tag = tag;
    this->property = property;
    this->collection = c;
    this->filteredItems = this->filterItems(this->collection, tag, property);
}


/** Цикличное получение элементов коллекции
 * @brief CircleVehicleIterator::getNext
 * @return
 */
TemplateVehicle * CircleVehicleIterator::getNext() {
    currentItem += 1;
    if (this->hasMore()) {
        return collection->getItem(this->filteredItems[currentItem]);
    } else {
        currentItem = 0;
        return collection->getItem(this->filteredItems[currentItem]);
    }
}


/** проверка, есть ли ещё элементы в коллекции
 * @brief CircleVehicleIterator::hasMore
 * @return
 */
bool CircleVehicleIterator::hasMore() {
    return currentItem < filteredItems.size();
}


/** Конструктор цикличного итератора
 * @brief OneDirectionIterator::CircleVehicleIterator
 * @param c
 * @param tag
 * @param property
 */
OneDirectionIterator::OneDirectionIterator(Collection *c, std::string tag, std::string property) : VehicleIterator(c, tag, property) {
    this->tag = tag;
    this->property = property;
    this->collection = c;
    this->filteredItems = this->filterItems(this->collection, tag, property);
}


/** Цикличное получение элементов коллекции
 * @brief OneDirectionIterator::getNext
 * @return
 */
TemplateVehicle * OneDirectionIterator::getNext() {
    if (this->hasMore()) {
        currentItem += 1;
        return collection->getItem(this->filteredItems[currentItem]);
    }
}


/** проверка, есть ли ещё элементы в коллекции
 * @brief OneDirectionIterator::hasMore
 * @return
 */
bool OneDirectionIterator::hasMore() {
    return currentItem+1 < filteredItems.size();
}


/** Конструктор цикличного итератора с сортировкой
 * @brief CircleSortIterator::CircleSortIterator
 * @param c
 * @param tag
 * @param property
 */
CircleSortIterator::CircleSortIterator(Collection *c, std::string tag, std::string property) : SortIterator(c, tag, property) {
    this->tag = tag;
    this->property = property;
    this->reversed = false;
    this->collection = c;
    this->collectionSize = 0;
    this->filteredItems = this->filterItems(this->collection, tag, property);
}


/** Цикличное получение следующего элемента
 * @brief CircleSortIterator::getNext
 * @return
 */
TemplateVehicle * CircleSortIterator::getNext() {
    this->getSorted();
    currentItem += 1;
    if (this->hasMore()) {
        return collection->getItem(this->preSorted[currentItem]);
    } else {
        currentItem = 0;
        return collection->getItem(this->preSorted[currentItem]);
    }
}


/** Проверка, еслть ли ещё элементы в коллекции
 * @brief CircleSortIterator::hasMore
 * @return
 */
bool CircleSortIterator::hasMore() {
    this->getSorted();
    return this->currentItem < this->preSorted.size();
}


/** Сортировка элементов
 * @brief CircleSortIterator::getSorted
 */
void CircleSortIterator::getSorted() {
    this->collectionSize = this->collection->getLength();
    this->preSorted = this->sortingAlgorithm->sort(this->collection, this->filteredItems, this->property, this->reversed);
}

/** Конструктор однонаправленного итератора с сортировкой
 * @brief OneDirectionSortIterator::CircleSortIterator
 * @param c
 * @param tag
 * @param property
 */
OneDirectionSortIterator::OneDirectionSortIterator(Collection *c, std::string tag, std::string property) : SortIterator(c, tag, property) {
    this->tag = tag;
    this->property = property;
    this->reversed = false;
    this->collection = c;
    this->collectionSize = 0;
    this->filteredItems = this->filterItems(this->collection, tag, property);
}


/** Однонаправленное получение следующего элемента
 * @brief OneDirectionSortIterator::getNext
 * @return
 */
TemplateVehicle * OneDirectionSortIterator::getNext() {
    this->getSorted();
    if (this->hasMore()) {
        currentItem += 1;
        return collection->getItem(this->preSorted[currentItem]);
    }
}


/** Проверка, еслть ли ещё элементы в коллекции
 * @brief OneDirectionSortIterator::hasMore
 * @return
 */
bool OneDirectionSortIterator::hasMore() {
    this->getSorted();
    return this->currentItem+1 < this->preSorted.size();
}


/** Сортировка элементов
 * @brief OneDirectionSortIterator::getSorted
 */
void OneDirectionSortIterator::getSorted() {
    this->collectionSize = this->collection->getLength();
    this->preSorted = this->sortingAlgorithm->sort(this->collection, this->filteredItems, this->property, this->reversed);
}
