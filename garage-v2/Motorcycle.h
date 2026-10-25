#ifndef MOTORCYCLE_H
#define MOTORCYCLE_H
#include "Vehicle.h"
#include <string>
#include <iostream>
class Motorcycle : public Vehicle {

    private: 
        bool sidecar;
    public: 
        Motorcycle(const std::string& plate, const std::string& companyName, const std::string& model, int year, bool sidecar= false);
        void describe(std::ostream& os) const override;
        bool hasSideCar() const;
        size_t spaceRequired() const override;
        Motorcycle* clone() const override;
        void save(std::ostream& os) const override;
};
#endif  


