#include <iostream>
#include "collection.h"
#include "iterator.h"
#include "objects.h"
#include "misc.h"

int main()
{
    Collection * c;
    AbstractVehicleIterator * iterator;
    std::string inputString = "",
            finishPhrase="finish",
            restartPhrase="restart",
            addCommand="add",
            nextCommand="next";
    Misc m = Misc();
    AbstractVehicle * av;

    while (inputString != finishPhrase) {
        c = new AircraftCollection();

        std::cout << "Input iterator to create(Circle, One): ";
        std::cin  >> inputString;

        if (m.matchCount(inputString, "Circle")) {
            iterator = new CircleVehicleIterator(c);
        } else if (m.matchCount(inputString, "One")) {
            iterator = new OneDirectionalIterator(c);
        } else {
            std::cout << "No such iterator exist. Please retry." << std::endl;
            continue;
        }
        while (inputString != finishPhrase && inputString != restartPhrase) {
            std::cout << "Input command("
                      << addCommand    << ", "
                      << nextCommand   << ", "
                      << restartPhrase << ", "
                      << finishPhrase  << ", "
                      << "): ";

            std::cin >> inputString;

            if (m.startsWith(inputString, addCommand)) {
                std::cout << "Input vehicle to add(Air, Miss, Quad): ";
                std::cin >> inputString;

                if (m.matchCount(inputString, "Aircraft")) {
                    av = new Aircraft();
                    c->pushBack(av);
                } else if (m.matchCount(inputString, "Missile")) {
                    av = new Missile();
                    c->pushBack(av);
                } else if (m.matchCount(inputString, "Quadrocopter")) {
                    av = new Quadrocopter();
                    c->pushBack(av);
                } else {
                    std::cout << "No known vehicle with name: " << inputString << ". Retry." << std::endl;
                }
            }
            if (m.startsWith(inputString, nextCommand)) {
                av = iterator->getNext();
                av->move();
            }
        }
    }
}
