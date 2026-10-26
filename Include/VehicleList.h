#ifndef VEHICLE_LIST_H
#define VEHICLE_LIST_H

#include "Vehicle.h"

struct VehicleNode {
    Vehicle data;
    VehicleNode* next;

    VehicleNode(const Vehicle& vehicle)
        : data(vehicle), next(nullptr) {
    }
};

class VehicleList {
private:
    VehicleNode* head;
    int count;

public:
    VehicleList();
    ~VehicleList();

    bool isEmpty() const;
    int getCount() const;

    void addVehicle(const Vehicle& vehicle);
    void displayVehicles() const;
    VehicleNode* findVehicle(int vehicleID) const;
    bool removeVehicle(int vehicleID);

    VehicleList(const VehicleList&) = delete;
    VehicleList& operator=(const VehicleList&) = delete;
};

#endif