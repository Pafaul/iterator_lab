#ifndef OBJECTS_H
#define OBJECTS_H
#include <iostream>


class AbstractVehicle {
protected:
    double x,y;
public:
    AbstractVehicle() {};
    AbstractVehicle(double x, double y) { this->x = x; this->y = y; };
    virtual void move() {};
};

class Aircraft : public AbstractVehicle {
public:
    Aircraft() : AbstractVehicle() { this->x = 0; this->y = 0; };
    Aircraft(double x, double y) : AbstractVehicle(x, y) {};
    void move() override;
};

class Missile : public AbstractVehicle {
public:
    Missile() : AbstractVehicle() { this->x = 0; this->y = 0; };
    Missile(double x, double y) : AbstractVehicle(x, y) {};
    void move() override;
};

class Quadrocopter : public AbstractVehicle {
public:
    Quadrocopter() : AbstractVehicle() { this->x = 0; this->y = 0; };
    Quadrocopter(double x, double y) : AbstractVehicle(x, y) {};
    void move() override;
};

class Helicopter : public AbstractVehicle {
public:
    Helicopter() : AbstractVehicle() { this->x = 0; this->y = 0; };
    Helicopter(double x, double y) : AbstractVehicle(x, y) {};
    void move() override;
};


#endif // OBJECTS_H
