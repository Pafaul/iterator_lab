#include "collection.h"

/** Создание пустой коллекции средств передвижения
 * @brief VehicleCollection::VehicleCollection
 */
VehicleCollection::VehicleCollection() : Collection() {
    items = std::vector<TemplateVehicle*>();
}

/** Добавление нового элемента в конец коллекции\
 * @brief VehicleCollection::pushBack
 * @param vehicle
 * @return
 */
int VehicleCollection::pushBack(TemplateVehicle *vehicle) {
    items.push_back(vehicle);
    return items.size();
}

/** Получение элемента по индексу
 * @brief VehicleCollection::getItem
 * @param index
 * @return
 */
TemplateVehicle* VehicleCollection::getItem(int index) {
     if (index < this->getLength() && index >= 0) return items[index];
}

/** Получение размера коллекции
 * @brief VehicleCollection::getLength
 * @return
 */
int VehicleCollection::getLength() {
    return this->items.size();
}
