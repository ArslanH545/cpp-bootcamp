#include "Garage.h"
#include "Car.h"
#include "Truck.h"
#include "Motorcycle.h"
#include <iostream>
#include "sorting.h"
#include <vector>
#include <limits>
#include <stdexcept>

using namespace std;

void printMenu();
int readInt(const string &prompt);
double readDouble(const string& prompt);
Vehicle* enterVehicleInput();
void toLowercase(string &s);
void readVehicleDetails(string& plate, string& companyName, string& model, int& year);

int main() {
    Garage g("Main", 10);
    while (true) {
        printMenu();

        int choice = readInt("Enter choice: ");

        switch (choice) {
            case 0: {
                cout << "Bye!" << endl;
                return 0;
            }
            case 1: {
                if (g.getCapacity() == g.getUsedspace()){
                    cout << "Garage is Full" << endl;
                } else {
                   if (g.park(enterVehicleInput())) {
                    cout << "Parked\n";
                    }
                    else { 
                        cout << "Could not park (duplicate plate or not enough space)\n";
                    }
                }
                cout << endl;
                break;
            }

            case 2: {
                string plate;
                cout << "Enter plate: ";
                cin >> plate;
                if (g.removeByPlate(plate)){
                    cout << "Successfully vehicle remove from the Garage!\n";
                } else {
                    cout << "Not found!\n";
                }
                cout << endl;
                break;
            }

            case 3: {
                string plate; 
                cout << "Enter plate: ";
                cin >> plate;
                const Vehicle* const v = g.findByPlate(plate);
                if (v != nullptr){
                    cout << *v << endl;
                } else {
                    cout << "Not found\n";
                }
                cout << endl;
                break;
            }

            case 4: {
                g.list(cout);
                cout << endl;
                break;
            }

            case 5:{
                g.sortedByPlate();
                cout << endl;
                break;
            }

            case 6: {
                cout << g.remainingSpace() << endl;
                cout << endl;
                break;
            }

            default:
                cout << "Unknown option" << endl;
        }
    }
    return 0;
}

void printMenu(){
    cout << "=== Garage ===" << endl;
    cout << "1. Park" << endl;
    cout << "2. Remove by plate" << endl;
    cout << "3. Find by plate" << endl;
    cout << "4. List" << endl;
    cout << "5. Sort by plate" << endl;
    cout << "6. Remaining space" << endl;
    cout << "0. Quit" << endl;
}

#include <iostream>
#include <limits>
#include <string>
using namespace std;

int readInt(const string& prompt) {
    while (true) {
        cout << prompt;

        int x;

        if (cin >> x) {
            return x;
        }

        if (cin.eof()) {
            throw runtime_error("Input ended");
        }

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Invalid number, try again.\n";
    }
}

double readDouble(const string& prompt) {
    while (true) {
        cout << prompt;

        double x;
        if (cin >> x) {
            return x;
        }

        if (cin.eof()) {
            throw runtime_error("Input ended");
        }

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Invalid number, try again.\n";
    }
}


void toLowercase(string &s){
    for (char& c: s){
        c = tolower(c);
    }
}


void readVehicleDetails(string& plate, string& companyName, string& model, int& year) {
    cout << "Enter Plate: ";
    cin >> plate;
    cout << "Company name: ";
    cin >> companyName;
    cout << "Model: ";
    cin >> model;
    year = readInt("Model year: ");
}

Vehicle* enterVehicleInput(){
    string plate, companyName, model, vehicleType;
    int year;
    while (true) {
        cout << "Vehicle type (Car, Truck, Motorcycle): ";
        cin >> vehicleType;
        toLowercase(vehicleType);
        if (vehicleType == "car"){
            readVehicleDetails(plate, companyName, model,year);
            int numOfDoors;
            numOfDoors = readInt("Enter number of doors: ");
            return new Car(plate, companyName, model, year, numOfDoors);
        } else if (vehicleType == "motorcycle") {
            readVehicleDetails(plate, companyName, model,year);
            int sidecar;
            do {
                sidecar = readInt("Have sidecar? (1 = Yes, 0 = No): ");
            } while (sidecar != 0 && sidecar != 1);
            bool hasSidecar = (sidecar == 1);
            return new Motorcycle(plate, companyName, model, year, hasSidecar);
        } else if (vehicleType == "truck"){
            readVehicleDetails(plate, companyName, model,year);
            double payloadTons = readDouble("Enter payload in Tons: ");
            return new Truck(plate, companyName, model, year, payloadTons);
        }
        cout << "Invalid Vehicle Type\nPlease enter again correct\n";
    }
}
