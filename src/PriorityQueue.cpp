
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

    // Higher number means higher priority.
    int newPriority = 0;

    if (passenger.isSenior && passenger.hasDisability) {
        newPriority = 3;
    } else if (passenger.hasDisability) {
        newPriority = 2;
    } else if (passenger.isSenior) {
        newPriority = 1;
    }

    // Insert at the front if the queue is empty
    // or the new passenger has higher priority.
    if (front == nullptr) {
        front = newNode;
    } else {
        int frontPriority = 0;

        if (front->data.isSenior && front->data.hasDisability) {
            frontPriority = 3;
        } else if (front->data.hasDisability) {
            frontPriority = 2;
        } else if (front->data.isSenior) {
            frontPriority = 1;
        }

        if (newPriority > frontPriority) {
            newNode->next = front;
            front = newNode;
        } else {
            PassengerNode* current = front;

            while (current->next != nullptr) {
                int nextPriority = 0;

                if (current->next->data.isSenior &&
                    current->next->data.hasDisability) {
                    nextPriority = 3;
                } else if (current->next->data.hasDisability) {
                    nextPriority = 2;
                } else if (current->next->data.isSenior) {
                    nextPriority = 1;
                }

                if (newPriority > nextPriority) {
                    break;
                }

                current = current->next;
            }

            newNode->next = current->next;
            current->next = newNode;
        }
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
