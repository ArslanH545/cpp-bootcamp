#ifndef CAR_H
#define CAR_H
#include "Vehicle.h"
#include <iostream>
#include <string>

class Car : public Vehicle{
    private:
        int numOfDoors;
    public:
        Car(const std::string& plate, const std::string& companyName, const std::string& model, const int year, const int numOfDoors);
        void describe(std::ostream& os) const override;
        int getNumofDoors() const;
        size_t spaceRequired() const override;
        Car* clone() const override;
        void save(std::ostream& os) const override;
};
#endif