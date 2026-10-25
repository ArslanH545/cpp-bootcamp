#include <iostream>
#include "Motorcycle.h"

Motorcycle::Motorcycle(const std::string& plate, const std::string& companyName, const std::string& model, int year, bool sidecar) : Vehicle(plate, companyName, model, year), sidecar(sidecar) {}


void Motorcycle::describe(std::ostream& os) const {
    Vehicle::describe(os);
    os << (sidecar ? "it has side car!": "it does not have side car!") << std::endl;
}


bool Motorcycle::hasSideCar() const{
    return sidecar;
}

size_t Motorcycle::spaceRequired() const {
    return 1;
}   

Motorcycle* Motorcycle::clone() const{
    return new Motorcycle(*this);
}

void Motorcycle::save(std::ostream& os) const {
os << "MOTORCYCLE," << getPlate() << ',' << getCompanyName() << "," << getModel() << "," << getYear() << "," << sidecar << '\n';
}