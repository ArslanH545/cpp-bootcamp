# Garage v2 Project

Garage v2 is a C++ garage management system designed to strengthen my understanding of Object-Oriented Programming (OOP) and memory management.

The system allows users to park, remove, search, and manage different types of vehicles based on the garage's available capacity. Each vehicle requires a certain amount of space, and the garage determines whether it can accommodate the vehicle.

Throughout this project, I practiced fundamental OOP concepts such as encapsulation, inheritance, polymorphism, abstract classes, and structs, along with more advanced topics including deep copying, copy constructors, destructors, operator overloading, templates, and file I/O.

One of my main goals was to understand how C++ manages dynamically allocated objects, especially when multiple classes interact through pointers.


## Features
The program provides a menu-driven interface with the following operations:

- Park Vehicle: Add a Car, Truck, or Motorcycle if sufficient space is available and the license plate is not already registered.

- Remove Vehicle: Remove a parked vehicle using its license plate.

- Find Vehicle: Search for a specific vehicle by its license plate.

- List Vehicles: Display all vehicles currently parked in the garage.

- Sort Vehicles: Sort the vehicle collection using a custom templated insertion sort.

- Remaining Space: Check how much garage capacity is still available.

- Save to File: Save garage data to a CSV file.

- Load from File: Read previously saved vehicle data from a CSV file.



## Build & run
Compile and run the project using:

./build.sh

The project uses g++ with strict compiler warnings and runtime sanitizers.

The main compiler flags include:

-std=c++17 -Wall -Wextra -Werror -g
-fsanitize=address,undefined
-fno-omit-frame-pointer

These flags help detect compilation warnings, memory errors, undefined behavior, and other potential issues during development.


## Design 

Class Hierarchy

```Vehicle (abstract class)
│
├── Car
│   └── doors
│
├── Truck
│   └── payloadTons
│
└── Motorcycle
    └── hasSidecar
```
Main Components

Vehicle

An abstract base class that defines the common interface for all vehicle types.

Its pure virtual functions include:

describe()

save()

spaceRequired()

clone()

Garage

Manages the collection of parked vehicles using:

std::vector<Vehicle*>

The Garage class owns its vehicle objects and is responsible for releasing their memory. It also implements deep copying through clone().

VehicleFactory

Creates the appropriate vehicle object based on the vehicle type stored in a CSV record.

parseVehicle(line) → Vehicle*

sorting.h

Contains a templated insertion sort function that accepts a comparison function or callable.

insertionSort(vector<T>&, Compare)

Memory Ownership

Ownership rule: park() takes ownership of the vehicle pointer, and Garage is responsible for deleting the object, whether parking succeeds or fails.

This prevents memory leaks and double deletion.

File Format

Vehicle information is stored in CSV format, with the vehicle type as the first field.

Example records:

Car,ABC123,Toyota,Camry,2020,4
Truck,TRK456,Ford,F150,2022,3.5
Motorcycle,MOT789,Honda,CBR500R,2021,0

Each vehicle type has its own additional fields:

Car: Number of doors

Truck: Payload capacity in tons

Motorcycle: Whether a sidecar is attached (1 for yes, 0 for no)

The VehicleFactory uses the first field to determine which subclass to instantiate.


## Testing
The project includes test cases covering garage operations, vehicle management, and memory safety.

Testing documentation:

Test Results

Test Spreadsheet

To replay a test case:

./m < tests/t1.txt

The program was compiled with AddressSanitizer (ASan) and UndefinedBehaviorSanitizer (UBSan) to detect memory-related errors and undefined behavior.

The final tested version exited without reported memory leaks.


## What I learned
- difference between the shallow copy and deep copy. Copying a Garage with the compiler’s default copy constructor copied the Vehicle* pointers, so two garages shared one set of vehicles and the second destructor double-freed them. ASan caught it as heap-use-after-free. Fix: virtual clone() on Vehicle + a copy constructor and copy assignment on Garage that deep-copy.
- park() method have feature to delete temparory vehicle if vector vehicle does not claim the onwership. When you hand a vehicle to park(), it’s the garage’s problem now — you don’t delete it yourself. If parking works, the garage keeps it and cleans it up later. If parking fails (same plate already inside, or not enough room), park() deletes it right away. I did it this way because otherwise every rejected vehicle would leak, and if both sides tried to delete it you’d get a double-free. Simple rule: one owner.
- learned how to write abstract class. Vehicle is abstract: describe(), save(), spaceRequired() and clone() are pure virtual (= 0). That means there’s no such thing as a plain Vehicle — only a Car, Truck or Motorcycle. I ran into this writing the loader: new Vehicle(...) wouldn’t compile, which is exactly the point — the type tag in the file has to decide which real class to create. The base class forces every subclass to answer “how much space do you take” and “how do you save yourself” without the Garage ever knowing which type it’s holding.
- Both versions are the constructor. The difference is when the fields get their values. With assignment in the body (name = other.name;), each member is first default-constructed, then overwritten — two steps, and for a moment capacity and usedSpace hold garbage. With the initializer list (: name(other.name), capacity(other.capacity)), each member is built with its value from the start. It’s slightly faster, but the bigger reason is that const and reference members can’t be assigned afterwards, so the initializer list is the only way to set them. I used it in the main constructor and later fixed the copy constructor to match.
- I changed the inner loop index j from int to size_t to silence a sign-compare warning. size_t can’t be negative, so when j hit 0 and I did j - 1, it wrapped to 18,446,744,073,709,551,615 instead of −1, j >= 0 stayed true forever, and v[j] read 4 bytes before the array. ASan flagged it as a heap-buffer-overflow and UBSan said “unsigned offset overflowed.” Rule I took away: use size_t for indexes that only count up; use int when the value genuinely has to go below zero; and write the static_cast where the two meet instead of letting the compiler convert silently.