#include "sortingalgorythm.h"

/** Получение отсортированного вектора индексов элементов коллекции методом пузырька
 * @brief BubbleSort::sort
 * @param c
 * @param tag
 * @param property
 * @param reverse
 * @return
 */
std::vector<int> BubbleSort::sort(Collection* c, std::vector<int> tagVehicles, std::string property, bool reverse) {
    if (tagVehicles.size() > 1) {
        for (unsigned long i = 0; i < tagVehicles.size() - 1; i++)
            for (unsigned long j = 0; j < tagVehicles.size() - i - 1; j++)
                if (c->getItem(tagVehicles[j])->getProperty(property).getValue() > c->getItem(tagVehicles[j+1])->getProperty(property).getValue())
                    std::swap(tagVehicles[j], tagVehicles[j+1]);
    }
    if (reverse) {
        std::reverse(tagVehicles.begin(), tagVehicles.end());
    }
    return tagVehicles;
}

/** Получение отсортированного вектора индексов элементов коллекции методом сортировки выбором
 * @brief SelectionSort::sort
 * @param c
 * @param tag
 * @param property
 * @param reverse
 * @return
 */
std::vector<int> SelectionSort::sort(Collection* c, std::vector<int> tagVehicles, std::string property, bool reverse) {
    if (tagVehicles.size() > 1) {
        int i, j, minIndex;
        for (i = 0; i < tagVehicles.size(); i++) {
            minIndex = i;
            for (j = i+1; j < tagVehicles.size(); j++)
                if (c->getItem(tagVehicles[j])->getProperty(property).getValue() < c->getItem(tagVehicles[minIndex])->getProperty(property).getValue())
                    minIndex = j;
            std::swap(tagVehicles[minIndex], tagVehicles[i]);
        }
    }
    if (reverse) {
        std::reverse(tagVehicles.begin(), tagVehicles.end());
    }
    return tagVehicles;
}

/** Получение отсортированного вектора индексов элементов коллекции сортировкой методом вставки
 * @brief InsertionSort::sort
 * @param c
 * @param tag
 * @param property
 * @param reverse
 * @return
 */
std::vector<int> InsertionSort::sort(Collection* c, std::vector<int> tagVehicles, std::string property, bool reverse) {
    if (tagVehicles.size() > 1) {
        int i, key, keyIndex, j;
        for (i = 1; i < tagVehicles.size(); i++)
        {
            key = c->getItem(tagVehicles[i])->getProperty(property).getValue();
            keyIndex = tagVehicles[i];
            j = i - 1;
            while(j >= 0 && c->getItem(tagVehicles[j])->getProperty(property).getValue() > key)
            {
                tagVehicles[j+1] = tagVehicles[j];
                j = j - 1;
            }
            tagVehicles[j+1] = keyIndex;
        }
    }
    if (reverse) {
        std::reverse(tagVehicles.begin(), tagVehicles.end());
    }
    return tagVehicles;
}
