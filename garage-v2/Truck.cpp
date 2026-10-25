#include <iostream>
#include <string>
#include "Truck.h"

Truck::Truck(const std::string& plate, const std::string& companyName, const std::string& model, int year, double payloadTons) : Vehicle(plate, companyName, model, year), payloadTons(payloadTons) {}


void Truck::describe(std::ostream& os) const {
    Vehicle::describe(os);
    os << "Payload tons: " << payloadTons << std::endl;
}

double Truck::getPayloadTons() const {
    return payloadTons;
}

size_t Truck::spaceRequired() const {
    return 4;
}

Truck* Truck::clone() const {
    return new Truck(*this);
} 

void Truck::save(std::ostream& os) const {
os << "TRUCK," << getPlate() << ',' << getCompanyName() << "," << getModel() << "," << getYear() << "," << payloadTons << '\n';
}