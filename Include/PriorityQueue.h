#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <string>

struct Passenger {
    int passengerID;
    std::string name;
    bool isSenior;
    bool hasDisability;

    Passenger()
        : passengerID(0),
          name(""),
          isSenior(false),
          hasDisability(false) {
    }
};

struct PassengerNode {
    Passenger data;
    PassengerNode* next;

    PassengerNode(const Passenger& passenger)
        : data(passenger), next(nullptr) {
    }
};

class PriorityQueue {
private:
    PassengerNode* front;

public:
    PriorityQueue();
    ~PriorityQueue();

    bool isEmpty() const;
    void enqueue(const Passenger& passenger);
    bool dequeue(Passenger& passenger);
    void displayQueue() const;

    PriorityQueue(const PriorityQueue&) = delete;
    PriorityQueue& operator=(const PriorityQueue&) = delete;
};

#endif