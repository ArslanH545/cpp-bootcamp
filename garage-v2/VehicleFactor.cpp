#include <vector>
#include "Vehicle.h"
#include "Car.h"
#include "Motorcycle.h"
#include "Truck.h"
#include <string>
#include <exception>

std::vector<std::string> split(std::string str, const std::string& delimiter){
    std::vector<std::string> tokens;
    size_t pos = 0;
    std::string token;
    while ((pos = str.find(delimiter)) != std::string::npos){
        token = str.substr(0, pos);
        tokens.push_back(token);
        str.erase(0, pos + delimiter.length());
    }
    tokens.push_back(str);
    return tokens;
}

void toLowercase(std::string &s){
     for (char& c: s){
        c = tolower(c);
    }
}


Vehicle* parseVehicle(const std::string& line){
    std::vector<std::string> tokens = split(line, ",");
    if (tokens.size() != 6) {
        return nullptr;
    }
    toLowercase(tokens[0]);
    try {
        int year = stoi(tokens[4]);
        if (tokens[0] == "car"){
            int numOfDoors    = std::stoi(tokens[5]);
            return new Car(tokens[1], tokens[2], tokens[3], year, numOfDoors);
        } else if (tokens[0] == "motorcycle") {
            int x = stoi(tokens[5]);
            if (x>= 0 && x <= 1){
                bool hasSideCar = (x != 0);
                return new Motorcycle(tokens[1], tokens[2], tokens[3], year, hasSideCar);
            } 
            return nullptr;
        } else if (tokens[0] == "truck") {
            return new Truck(tokens[1], tokens[2], tokens[3], year, std::stod(tokens[5]));
        } else {
            return nullptr;
        }
    } catch (std::invalid_argument&) {
        return nullptr;
    } catch (std::out_of_range&) {
        return nullptr;
    }
}   