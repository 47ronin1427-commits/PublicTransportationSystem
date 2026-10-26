#ifndef CIRCULAR_QUEUE_H
#define CIRCULAR_QUEUE_H

#include "Vehicle.h"

class CircularQueue {
private:
    Vehicle* items;
    int capacity;
    int front;
    int rear;
    int count;

public:
    explicit CircularQueue(int size);
    ~CircularQueue();

    bool isEmpty() const;
    bool isFull() const;
    bool enqueue(const Vehicle& vehicle);
    bool dequeue(Vehicle& vehicle);
    void displayQueue() const;

    CircularQueue(const CircularQueue&) = delete;
    CircularQueue& operator=(const CircularQueue&) = delete;
};

#endif