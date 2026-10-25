#include <iostream>
#include "Garage.h"
#include "Vehicle.h"
#include "sorting.h"

void Garage::clear(){
    usedSpace = 0;
    for (Vehicle* v: vehicles){
        delete v;
    }
     // drops all the (now dangling) pointers; size() becomes 0, capacity() unchanged
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

Garage::Garage(const Garage& other) : name(other.name), capacity(other.capacity), usedSpace(other.usedSpace){
    usedSpace = other.usedSpace;
 }


// Always takes ownership of v. If it returns false, v has already been deleted: do not use it.
bool Garage::park(Vehicle* v) {
    if (v == nullptr){
        return false;
    }
    if (indexOf(v->getPlate()) != -1) {
        delete v;
        return false;
    }
    const std::size_t space = v->spaceRequired();
    if (usedSpace + space > capacity) {
        delete v;
        return false;
    }
    vehicles.push_back(v);
    usedSpace += space;
    return true;
}

bool Garage::removeByPlate(const std::string& plate){
    int index = indexOf(plate);
    if (index == -1){
        return false;
    } 
    Vehicle* v = vehicles[static_cast<size_t>(index)];
    size_t spaceOccupiedByVehicle = v->spaceRequired();
    // object on heap is being destroyed, old address is there. 
    delete v;
    // need to remove the old address
    vehicles.erase(vehicles.begin() + index);
    usedSpace -= spaceOccupiedByVehicle;
    return true;
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

std::size_t Garage::remainingSpace() const{
    return (capacity - usedSpace);
}


int Garage::indexOf(const std::string& plate) const{
    for (std::size_t i = 0; i < vehicles.size(); i++){
        if (vehicles[i]->getPlate() == plate) {
            return static_cast<int>(i);
        }
    }
    return -1;
}

const Vehicle* Garage::findByPlate(const std::string& plate) const {
    int index = indexOf(plate);
    if (index == -1){
        return nullptr;
    } 
    return vehicles.at(static_cast<std::size_t>(index));
}



void Garage::sortedByPlate(){
    insertionSort(vehicles, [](const Vehicle *v1, const Vehicle *v2) {
        return v1->getPlate() < v2->getPlate();
    });
}


std::size_t Garage::getUsedspace() const{
    return usedSpace;
}

std::size_t Garage::getCapacity() const{
    return capacity;
}