// Decleration what vehicle has/can do
#ifndef VEHICLE_H
#define VEHICLE_H
#include <string>
#include <iostream>
#include <vector> 
class Vehicle {
    friend std::ostream& operator<<(std::ostream& os, const Vehicle& v);
    private:
         static int count;
    protected:
        std::string plate;
        std::string companyName;
        std::string model;
        int year;
    public:
        Vehicle(const std::string& plate, const std::string& companyName, const std::string& model, const int year);
        // virtual destructor → correct destruction through Vehicle*
        virtual ~Vehicle();
        // copy constructor 
        Vehicle(const Vehicle& other);
        // Getters
        const std::string& getPlate() const;
        const std::string& getCompanyName() const;
        const std::string& getModel() const;
        int getYear() const;
        // runtime polymorphism // pure virtual function.
        virtual void describe(std::ostream& os) const = 0;  
        virtual void save(std::ostream& os) const = 0;  
        // count the Total vehicle, it does not belong to specifc object rather it belong entire Vehicle class.   
        static int getCount();
        // how much space is avaible for each Vehcile type in garage. 
        virtual size_t spaceRequired() const = 0;
        virtual Vehicle* clone() const = 0;
};
#endif