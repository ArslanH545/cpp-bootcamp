#ifndef GARAGE_H
#define GARAGE_H
#include <vector>
#include "Vehicle.h"
class Garage {
    friend std::ostream& operator<<(std::ostream& os, const Garage& g);
    private:
        std::string name;
        std::vector<Vehicle*> vehicles;
        // size_t can not be negative.
        std::size_t capacity;
        std::size_t usedSpace;
        void clear();
        void copyVehiclesForm(const Garage& other);
    public:
        Garage(const std::string& name, const std::size_t capacity);
        ~Garage();
        // deep copy contrcutor
        Garage(const Garage& other);
        bool park(Vehicle* vehicle);
        void list(std::ostream& os) const;
        Garage& operator=(const Garage& other);
        std::size_t remainingSpace() const;
};
#endif