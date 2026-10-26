#ifndef DISPATCH_STACK_H
#define DISPATCH_STACK_H

#include "Vehicle.h"

struct DispatchNode {
    Vehicle data;
    DispatchNode* next;

    DispatchNode(const Vehicle& vehicle)
        : data(vehicle), next(nullptr) {
    }
};

class DispatchStack {
private:
    DispatchNode* topNode;

public:
    DispatchStack();
    ~DispatchStack();

    bool isEmpty() const;
    void push(const Vehicle& vehicle);
    bool pop(Vehicle& vehicle);
    bool peek(Vehicle& vehicle) const;
    void displayStack() const;

    DispatchStack(const DispatchStack&) = delete;
    DispatchStack& operator=(const DispatchStack&) = delete;
};

#endif