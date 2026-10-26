#include <iostream>
#include <limits>
#include <string>

#include "Vehicle.h"
#include "VehicleList.h"
#include "CircularQueue.h"
#include "PriorityQueue.h"
#include "DispatchStack.h"
#include "Benchmark.h"

using namespace std;

int main() {
    VehicleList fleet;
    CircularQueue bayQueue(10);
    PriorityQueue passengerQueue;
    DispatchStack dispatchHistory;

    int choice;

    do {
        cout << "\n========================================\n";
        cout << " PUBLIC TRANSPORTATION DISPATCH SYSTEM\n";
        cout << "========================================\n";
        cout << "1. Add Vehicle\n";
        cout << "2. Display Vehicles\n";
        cout << "3. Search Vehicle\n";
        cout << "4. Remove Vehicle\n";
        cout << "5. Add Vehicle to Bay Queue\n";
        cout << "6. Display Bay Queue\n";
        cout << "7. Dispatch Next Vehicle\n";
        cout << "8. Add Passenger\n";
        cout << "9. Display Passenger Queue\n";
        cout << "10. Serve Next Passenger\n";
        cout << "11. Record Dispatch\n";
        cout << "12. Display Dispatch History\n";
        cout << "13. Undo Latest Dispatch Record\n";
        cout << "14. Run Sorting and Searching Benchmark\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";

        if (!(cin >> choice)) {
            cout << "Invalid input. Please enter a number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            choice = -1;
            continue;
        }

        switch (choice) {
        case 1: {
            Vehicle vehicle;

            cout << "Enter Vehicle ID: ";
            if (!(cin >> vehicle.vehicleID)) {
                cout << "Invalid vehicle ID.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            }

            if (fleet.findVehicle(vehicle.vehicleID) != nullptr) {
                cout << "That vehicle ID already exists.\n";
                break;
            }

            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Enter Route Name: ";
            getline(cin, vehicle.routeName);

            cout << "Enter Driver Name: ";
            getline(cin, vehicle.driverName);

            cout << "Enter Seating Capacity: ";
            if (!(cin >> vehicle.seatingCapacity) ||
                vehicle.seatingCapacity <= 0) {
                cout << "Capacity must be a positive number.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            }

            cout << "Enter Passenger Queue Count: ";
            if (!(cin >> vehicle.passengerQueueCount) ||
                vehicle.passengerQueueCount < 0) {
                cout << "Passenger count cannot be negative.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            }

            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Enter Departure Status (Waiting/Ready/Departed): ";
            getline(cin, vehicle.departureStatus);

            fleet.addVehicle(vehicle);
            cout << "Vehicle added successfully.\n";
            break;
        }

        case 2:
            fleet.displayVehicles();
            break;

        case 3: {
            int id;
            cout << "Enter Vehicle ID to search: ";

            if (!(cin >> id)) {
                cout << "Invalid ID.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            }

            VehicleNode* found = fleet.findVehicle(id);

            if (found != nullptr) {
                cout << "Vehicle found: " << found->data.routeName
                     << " | Driver: " << found->data.driverName << '\n';
            } else {
                cout << "Vehicle not found.\n";
            }
            break;
        }

        case 4: {
            int id;
            cout << "Enter Vehicle ID to remove: ";

            if (!(cin >> id)) {
                cout << "Invalid ID.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            }

            if (fleet.removeVehicle(id)) {
                cout << "Vehicle removed.\n";
            } else {
                cout << "Vehicle not found.\n";
            }
            break;
        }

        case 5: {
            int id;
            cout << "Enter Vehicle ID for the bay queue: ";

            if (!(cin >> id)) {
                cout << "Invalid ID.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            }

            VehicleNode* found = fleet.findVehicle(id);

            if (found == nullptr) {
                cout << "Add the vehicle to the fleet first.\n";
            } else {
                bayQueue.enqueue(found->data);
            }
            break;
        }

        case 6:
            bayQueue.displayQueue();
            break;

        case 7: {
            Vehicle vehicle;

            if (bayQueue.dequeue(vehicle)) {
                cout << "Dispatching Vehicle " << vehicle.vehicleID
                     << " on route " << vehicle.routeName << ".\n";

                vehicle.departureStatus = "Departed";
                dispatchHistory.push(vehicle);
            }
            break;
        }

        case 8: {
            Passenger passenger;
            char answer;

            cout << "Enter Passenger ID: ";
            if (!(cin >> passenger.passengerID)) {
                cout << "Invalid passenger ID.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            }

            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Enter Passenger Name: ";
            getline(cin, passenger.name);

            cout << "Is the passenger a senior citizen? (y/n): ";
            cin >> answer;
            passenger.isSenior = (answer == 'y' || answer == 'Y');

            cout << "Is the passenger a PWD? (y/n): ";
            cin >> answer;
            passenger.hasDisability = (answer == 'y' || answer == 'Y');

            passengerQueue.enqueue(passenger);
            break;
        }

        case 9:
            passengerQueue.displayQueue();
            break;

        case 10: {
            Passenger passenger;

            if (passengerQueue.dequeue(passenger)) {
                cout << "Now serving: " << passenger.name
                     << " (ID: " << passenger.passengerID << ")\n";
            }
            break;
        }

        case 11: {
            int id;
            cout << "Enter Vehicle ID to record: ";

            if (!(cin >> id)) {
                cout << "Invalid ID.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            }

            VehicleNode* found = fleet.findVehicle(id);

            if (found != nullptr) {
                dispatchHistory.push(found->data);
            } else {
                cout << "Vehicle not found in fleet.\n";
            }
            break;
        }

        case 12:
            dispatchHistory.displayStack();
            break;

        case 13: {
            Vehicle vehicle;

            if (dispatchHistory.pop(vehicle)) {
                cout << "Removed latest dispatch record for Vehicle "
                     << vehicle.vehicleID << ".\n";
            }
            break;
        }


case 14: {
    Benchmark::runFullSuite();
    break;
}

        case 0:
            cout << "Exiting system. Goodbye!\n";
            break;

        default:
            cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != 0);

    return 0;
}