#include <iostream>
#include "VehicleList.h"

using namespace std;

VehicleList::VehicleList() {
    head = nullptr;
    count = 0;
}

VehicleList::~VehicleList() {
    VehicleNode* current = head;

    while (current != nullptr) {
        VehicleNode* nextNode = current->next;
        delete current;
        current = nextNode;
    }

    head = nullptr;
    count = 0;
}

bool VehicleList::isEmpty() const {
    return head == nullptr;
}

int VehicleList::getCount() const {
    return count;
}

void VehicleList::addVehicle(const Vehicle& vehicle) {
    VehicleNode* newNode = new VehicleNode(vehicle);

    if (head == nullptr) {
        head = newNode;
    } else {
        VehicleNode* current = head;

        while (current->next != nullptr) {
            current = current->next;
        }

        current->next = newNode;
    }

    count++;
}

void VehicleList::displayVehicles() const {
    if (head == nullptr) {
        cout << "No vehicles registered.\n";
        return;
    }

    VehicleNode* current = head;

    while (current != nullptr) {
        cout << "\nVehicle ID: "
             << current->data.vehicleID << endl;
        cout << "Route: "
             << current->data.routeName << endl;
        cout << "Driver: "
             << current->data.driverName << endl;
        cout << "Seating Capacity: "
             << current->data.seatingCapacity << endl;
        cout << "Passengers Waiting: "
             << current->data.passengerQueueCount << endl;
        cout << "Departure Status: "
             << current->data.departureStatus << endl;

        current = current->next;
    }
}

VehicleNode* VehicleList::findVehicle(int vehicleID) const {
    VehicleNode* current = head;

    while (current != nullptr) {
        if (current->data.vehicleID == vehicleID) {
            return current;
        }

        current = current->next;
    }

    return nullptr;
}

bool VehicleList::removeVehicle(int vehicleID) {
    if (head == nullptr) {
        return false;
    }

    if (head->data.vehicleID == vehicleID) {
        VehicleNode* temp = head;
        head = head->next;

        delete temp;
        count--;

        return true;
    }

    VehicleNode* current = head;

    while (current->next != nullptr) {
        if (current->next->data.vehicleID == vehicleID) {
            VehicleNode* temp = current->next;

            current->next = temp->next;

            delete temp;
            count--;

            return true;
        }

        current = current->next;
    }

    return false;
}