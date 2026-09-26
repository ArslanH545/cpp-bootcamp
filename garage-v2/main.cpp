#include "Garage.h"
#include "Car.h"
#include "Truck.h"
#include <iostream>
using namespace std;

int main() {
    Garage a("A", 10);
    a.park(new Car("AAA111", "Toyota", "Camry", 2015, 4));          // 2 units
    a.park(new Truck("TTT222", "Ford", "F-150", 2023, 7.5));        // 4 units -> used 6/10

    Garage b("B", 5);
    b.park(new Car("BBB333", "Honda", "Civic", 2018, 4));           // 2 units -> used 2/5

    std::cout << "count before: " << Vehicle::getCount() << '\n';  // 3

    b = a;   // 1. assign over non-empty: B's Civic must be deleted
    std::cout << "after b=a: " << Vehicle::getCount() << '\n';     // 4

    #pragma clang diagnostic push
    #pragma clang diagnostic ignored "-Wself-assign-overloaded"
    b = b;   // 2. self-assignment
    #pragma clang diagnostic pop
        std::cout << "after b=b: " << Vehicle::getCount() << '\n';     // 4

    { Garage c = a; }   // 3. copy ctor, then c destroyed at }
    std::cout << "after scope: " << Vehicle::getCount() << '\n';   // 4

    cout << a << endl;  // 4. both valid, independent
    cout << b << endl;
}