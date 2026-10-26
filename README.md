# Public Transportation Dispatch and Commuter Queue System

## Project Overview

The Public Transportation Dispatch and Commuter Queue System is a C++ console application designed to manage public transportation vehicles, passenger queues, and dispatch records. It uses different data structures and sorting and searching algorithms to organize transportation operations.

## Features

1. **Vehicle Management:** Add, display, search, and remove vehicles from the fleet registry.
2. **Vehicle Bay Queue:** Manage vehicles waiting in the dispatch bay using a circular queue.
3. **Passenger Priority Queue:** Give priority to senior citizens and persons with disabilities (PWD).
4. **Dispatch Management:** Record vehicle dispatches using a stack and undo the latest dispatch record.
5. **Sorting Algorithms:** Implement Bubble Sort, Selection Sort, and Insertion Sort.
6. **Searching Algorithms:** Implement Linear Search and Binary Search.
7. **Performance Benchmarking:** Measure sorting and searching performance using execution time and comparison counts.

## Technologies Used

- C++
- C++ Standard Library
- Visual Studio Code
- MSYS2 GCC Compiler

## Project Structure

```text
PublicTransportationSystem/
├── main.cpp
├── include/
│   ├── Vehicle.h
│   ├── VehicleList.h
│   ├── CircularQueue.h
│   ├── PriorityQueue.h
│   ├── DispatchStack.h
│   └── Benchmark.h
├── src/
│   ├── Vehicle.cpp
│   ├── VehicleList.cpp
│   ├── CircularQueue.cpp
│   ├── PriorityQueue.cpp
│   ├── DispatchStack.cpp
│   └── Benchmark.cpp
├── docs/
└── README.md
```

## Requirements

- Visual Studio Code or another C++ editor
- MSYS2 or another compiler that supports C++17
- A terminal for compiling and running the program

## How to Compile

Open the terminal in the project directory and run:

```powershell
C:\msys64\ucrt64\bin\g++.exe -std=c++17 -Wall -Wextra -I include main.cpp src\Vehicle.cpp src\VehicleList.cpp src\CircularQueue.cpp src\PriorityQueue.cpp src\DispatchStack.cpp src\Benchmark.cpp -o transport.exe
```

## How to Run

After successful compilation, run:

```powershell
.\transport.exe
```

The application displays a menu where users can select the available vehicle management, queue management, dispatch, and benchmarking operations.

## Benchmarking

The benchmark module tests Bubble Sort, Selection Sort, and Insertion Sort using random, sorted, and reverse-sorted datasets. Dataset sizes include 100, 1,000, 10,000, and 50,000 elements.

The program records execution time, comparisons, and swaps or shifts for sorting algorithms. It also compares Linear Search and Binary Search using sorted datasets.

Some sorting tests involving 50,000 elements may take longer because the algorithms use nested loops.

## Data Structures Used

- **Singly Linked List:** Stores and manages registered vehicles.
- **Circular Queue:** Manages vehicles waiting in the dispatch bay.
- **Priority Queue:** Places senior citizens and PWD passengers ahead of regular passengers.
- **Stack:** Stores dispatch records and supports undoing the latest record.

## Notes

The benchmark execution times may vary depending on the computer and its current workload. Binary Search requires sorted data to work correctly.

## Author

Student Name: Ronin C. Gunday

Course/Section: IT 2.4

Instructor: Mr. Darwin Vargas