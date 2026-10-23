#include "Garage.h"
#include "Car.h"
#include "Truck.h"
#include "Motorcycle.h"
#include <iostream>
#include "sorting.h"
#include <vector>
using namespace std;

int main() {
    Garage g1 = {"Arslan", 10};
    g1.park(new Truck("123", "Toyota", "truck", 2015, 3));
    g1.park(new Motorcycle("987", "Busa", "ar", 2018));
    g1.park(new Car("000", "car", "ford", 2017, 4));
    cout << g1 << endl;
    g1.sortedByPlate();

    cout << g1 << endl;
    return 0;
}

