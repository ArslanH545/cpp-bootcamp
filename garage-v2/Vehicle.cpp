#include <iostream>
#include <string>
#include "Vehicle.h"

int Vehicle::count = 0;

Vehicle::Vehicle(const std::string& plate, const std::string& companyName, const std::string& model, const int year) : plate(plate), companyName(companyName), model(model), year(year) {
    ++count;
}
Vehicle::~Vehicle(){
    --count;
}

int Vehicle::getCount(){
    return count;
}
Vehicle::Vehicle(const Vehicle& other){
    plate = other.plate;
    companyName = other.companyName;
    model = other.model;
    year = other.year;
    ++count;
}

void Vehicle::describe(std::ostream& os) const {
    os << "Plate: " << plate << std::endl;
    os << "Company: " << companyName << std::endl;
    os << "Model: " << model << std::endl;
    os << "Year: " << year << std::endl;
}


std::ostream& operator<<(std::ostream& os, const Vehicle& v){
    v.describe(os);
    return os;
}

const std::string& Vehicle::getPlate() const{
    return plate;
}
const std::string& Vehicle::getCompanyName() const{
    return companyName;
}
const std::string& Vehicle::getModel() const{
    return model;
}
int Vehicle::getYear() const{
    return year;
}

