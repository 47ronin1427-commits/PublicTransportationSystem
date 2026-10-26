#ifndef VEHICLE_H
#define VEHICLE_H

#include <string>
using namespace std;

struct Vehicle {
    int vehicleID;
    string routeName;
    string driverName;
    int seatingCapacity;
    int passengerQueueCount;
    string departureStatus;

    Vehicle()
        : vehicleID(0),
          routeName(""),
          driverName(""),
          seatingCapacity(0),
          passengerQueueCount(0),
          departureStatus("Waiting") {
    }
};

#endif