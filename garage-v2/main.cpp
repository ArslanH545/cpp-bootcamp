#include "Garage.h"
#include "Car.h"
#include "Truck.h"
#include <iostream>
using namespace std;

int main() {
    Garage a("A", 10);
    a.park(new Car("AAA111", "Toyota", "Camry", 2015, 4));   // 2 units
    a.park(new Truck("AAA222", "Ford", "F-150", 2023, 7.5));        // 4 units -> used 6/10
    a.removeByPlate("AAA111");
    cout << a << endl;
    cout << Vehicle::getCount() << endl; // 0
    return 0;
}