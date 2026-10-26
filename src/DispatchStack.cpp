#include <iostream>
#include "DispatchStack.h"

using namespace std;

DispatchStack::DispatchStack() {
    topNode = nullptr;
}

DispatchStack::~DispatchStack() {
    while (topNode != nullptr) {
        DispatchNode* temp = topNode;
        topNode = topNode->next;
        delete temp;
    }
}

bool DispatchStack::isEmpty() const {
    return topNode == nullptr;
}

void DispatchStack::push(const Vehicle& vehicle) {
    DispatchNode* newNode = new DispatchNode(vehicle);

    newNode->next = topNode;
    topNode = newNode;

    cout << "Dispatch record added to stack.\n";
}

bool DispatchStack::pop(Vehicle& vehicle) {
    if (isEmpty()) {
        cout << "Dispatch stack is empty.\n";
        return false;
    }

    DispatchNode* temp = topNode;
    vehicle = temp->data;
    topNode = topNode->next;

    delete temp;
    return true;
}

bool DispatchStack::peek(Vehicle& vehicle) const {
    if (isEmpty()) {
        return false;
    }

    vehicle = topNode->data;
    return true;
}

void DispatchStack::displayStack() const {
    if (isEmpty()) {
        cout << "No dispatch records.\n";
        return;
    }

    DispatchNode* current = topNode;

    cout << "\n--- Dispatch Stack (Most Recent First) ---\n";

    while (current != nullptr) {
        cout << "Vehicle ID: " << current->data.vehicleID
             << " | Route: " << current->data.routeName
             << " | Driver: " << current->data.driverName
             << '\n';

        current = current->next;
    }
}