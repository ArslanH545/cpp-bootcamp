#ifndef VEHICLEFACTOR_CPP
#define VEHICLEFACTOR_CPP
#include <vector>
#include <string>
#include "Vehicle.h"
Vehicle* parseVehicle(const std::string& line);
std::vector<std::string> split(std::string str, const std::string& delimiter);
void toLowercase(std::string &s);
#endif