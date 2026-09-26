#include <iostream>
#include "Garage.h"
#include "Vehicle.h"


void Garage::clear(){
    for (Vehicle* v: vehicles){
        delete v;
    }
    // following vechile clear , 
    // while(!vehicles.empty()){
    //     vehicles.pop_back();
    // }
    vehicles.clear();
}

void Garage::copyVehiclesForm(const Garage& other){
    for (Vehicle* v: other.vehicles){
        vehicles.push_back(v->clone());
    }
}


Garage::Garage(const std::string& name, const std::size_t capacity) 
    : name(name), capacity(capacity), usedSpace(0) {}


Garage::~Garage(){
    clear();
}

Garage::Garage(const Garage& other){
    name = other.name;
    copyVehiclesForm(other);
    capacity = other.capacity;
    usedSpace = other.usedSpace;
 }

bool Garage::park(Vehicle* vehicle) {
    if (vehicle != nullptr) {
        const size_t vehicleSpace = vehicle->spaceRequired();
        if ( vehicleSpace + usedSpace <= capacity) {
            vehicles.push_back(vehicle);
            usedSpace += vehicleSpace;
            return true;
        }
    }
    return false;
}

void Garage::list(std::ostream& os) const {
    for (Vehicle* v: vehicles) {
        os << *(v) << std::endl;
    }
}


std::ostream& operator<<(std::ostream& os, const Garage& g){
    g.list(os);
    return os;
}

Garage& Garage::operator=(const Garage& other){
    // 1. Check self-assignment
        if (this == &other){
            return *this;
        }
    // 2. Delete this Garage's OLD vehicles
        clear();
    // 3. Copy normal fields
        name = other.name;
        capacity = other.capacity;
        usedSpace = other.usedSpace;
    // 4. Deep-copy other's vehicles
        copyVehiclesForm(other);
    // 5. return *this
    return *this;
}