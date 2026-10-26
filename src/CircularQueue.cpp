#include <iostream>
#include "CircularQueue.h"

using namespace std;

CircularQueue::CircularQueue(int size) {
    capacity = (size > 0) ? size : 1;
    items = new Vehicle[capacity];
    front = 0;
    rear = -1;
    count = 0;
}

CircularQueue::~CircularQueue() {
    delete[] items;
}

bool CircularQueue::isEmpty() const {
    return count == 0;
}

bool CircularQueue::isFull() const {
    return count == capacity;
}

bool CircularQueue::enqueue(const Vehicle& vehicle) {
    if (isFull()) {
        cout << "Vehicle queue is full.\n";
        return false;
    }

    rear = (rear + 1) % capacity;
    items[rear] = vehicle;
    count++;

    cout << "Vehicle added to the bay queue.\n";
    return true;
}

bool CircularQueue::dequeue(Vehicle& vehicle) {
    if (isEmpty()) {
        cout << "Vehicle queue is empty.\n";
        return false;
    }

    vehicle = items[front];
    front = (front + 1) % capacity;
    count--;

    return true;
}

void CircularQueue::displayQueue() const {
    if (isEmpty()) {
        cout << "No vehicles in the bay queue.\n";
        return;
    }

    cout << "\n--- Vehicle Bay Queue ---\n";

    for (int i = 0; i < count; i++) {
        int index = (front + i) % capacity;

        cout << "Vehicle ID: " << items[index].vehicleID
             << " | Route: " << items[index].routeName
             << " | Status: " << items[index].departureStatus
             << '\n';
    }
}