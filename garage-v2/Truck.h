#ifndef TRUCK_H
#define TRUCK_H
#include "Vehicle.h"
#include <string>
#include <iostream>
class Truck : public Vehicle{
    private:
        double payloadTons;
    public:
        Truck(const std::string& plate, const std::string& companyName, const std::string& model, int year, double payloadTons);
        void describe(std::ostream& os) const override;
        double getPayloadTons() const;
        size_t spaceRequired() const override;
        Truck* clone() const override;
        void save(std::ostream& os) const override;
};
#endif