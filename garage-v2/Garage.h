#ifndef GARAGE_H
#define GARAGE_H
#include <vector>
#include "Vehicle.h"
#include "sorting.h"

struct LoadFileResult {
    bool opened;
    int load;
    std::vector<std::string> rejected;
};

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
        int indexOf(const std::string& plate) const;
    public:
        Garage(const std::string& name, const std::size_t capacity);
        ~Garage();
        // deep copy contrcutor
        Garage(const Garage& other);
        bool park(Vehicle* vehicle);
        void list(std::ostream& os) const;
        Garage& operator=(const Garage& other);
        std::size_t remainingSpace() const;
        std::size_t getUsedspace() const;
        std::size_t getCapacity() const;
        const Vehicle* findByPlate(const std::string& plate) const;
        bool removeByPlate(const std::string& plate);
        void sortedByPlate();
        bool saveToFile(const std::string& path) const;
        LoadFileResult loadFromFile(const std::string& path);  
};

#endif