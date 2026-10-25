#include <iostream>
#include "Car.h"

Car::Car(const std::string& plate, const std::string& companyName, const std::string& model, const int year, const int numOfDoors) : Vehicle(plate, companyName, model, year), numOfDoors(numOfDoors) {}

void Car::describe(std::ostream& os) const {
    Vehicle::describe(os);
    os << "Number of doors: " << numOfDoors << std::endl;
}

int Car::getNumofDoors() const{
    return numOfDoors;
}

size_t Car::spaceRequired() const {
    return 2;
}

Car* Car::clone() const {
    return new Car(*this);
}

void Car::save(std::ostream& os) const {
os << "CAR," << getPlate() << ',' << getCompanyName() << "," << getModel() << "," << getYear() << "," << numOfDoors << '\n';
}