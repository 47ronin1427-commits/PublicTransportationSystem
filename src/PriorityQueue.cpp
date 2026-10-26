#include <iostream>
#include "PriorityQueue.h"

using namespace std;

PriorityQueue::PriorityQueue() {
    front = nullptr;
}

PriorityQueue::~PriorityQueue() {
    while (front != nullptr) {
        PassengerNode* temp = front;
        front = front->next;
        delete temp;
    }
}

bool PriorityQueue::isEmpty() const {
    return front == nullptr;
}

void PriorityQueue::enqueue(const Passenger& passenger) {
    PassengerNode* newNode = new PassengerNode(passenger);

    bool hasPriority = passenger.isSenior || passenger.hasDisability;

    if (front == nullptr) {
        front = newNode;
    } else if (hasPriority) {
        PassengerNode* current = front;

        if (!(current->data.isSenior || current->data.hasDisability)) {
            newNode->next = front;
            front = newNode;
        } else {
            while (current->next != nullptr &&
                   (current->next->data.isSenior ||
                    current->next->data.hasDisability)) {
                current = current->next;
            }

            newNode->next = current->next;
            current->next = newNode;
        }
    } else {
        PassengerNode* current = front;

        while (current->next != nullptr) {
            current = current->next;
        }

        current->next = newNode;
    }

    cout << "Passenger added to the queue.\n";
}

bool PriorityQueue::dequeue(Passenger& passenger) {
    if (isEmpty()) {
        cout << "Passenger queue is empty.\n";
        return false;
    }

    PassengerNode* temp = front;
    passenger = temp->data;
    front = front->next;

    delete temp;
    return true;
}

void PriorityQueue::displayQueue() const {
    if (isEmpty()) {
        cout << "No passengers waiting.\n";
        return;
    }

    PassengerNode* current = front;

    cout << "\n--- Passenger Priority Queue ---\n";

    while (current != nullptr) {
        cout << "ID: " << current->data.passengerID
             << " | Name: " << current->data.name
             << " | Senior: " << (current->data.isSenior ? "Yes" : "No")
             << " | PWD: " << (current->data.hasDisability ? "Yes" : "No")
             << '\n';

        current = current->next;
    }
}