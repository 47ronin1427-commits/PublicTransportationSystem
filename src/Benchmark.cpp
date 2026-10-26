#include <iostream>
#include <iomanip>
#include <chrono>
#include <algorithm>
#include <random>
#include <string>

#include "Benchmark.h"

using namespace std;
using namespace chrono;

SortMetrics Benchmark::bubbleSort(int values[], int size) {
    SortMetrics metrics;
    auto start = steady_clock::now();

    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            metrics.comparisons++;

            if (values[j] > values[j + 1]) {
                int temp = values[j];
                values[j] = values[j + 1];
                values[j + 1] = temp;
                metrics.swaps++;
            }
        }
    }

    auto end = steady_clock::now();
    metrics.elapsedMilliseconds =
        duration<double, milli>(end - start).count();

    return metrics;
}

SortMetrics Benchmark::selectionSort(int values[], int size) {
    SortMetrics metrics;
    auto start = steady_clock::now();

    for (int i = 0; i < size - 1; i++) {
        int minIndex = i;

        for (int j = i + 1; j < size; j++) {
            metrics.comparisons++;

            if (values[j] < values[minIndex]) {
                minIndex = j;
            }
        }

        if (minIndex != i) {
            int temp = values[i];
            values[i] = values[minIndex];
            values[minIndex] = temp;
            metrics.swaps++;
        }
    }

    auto end = steady_clock::now();
    metrics.elapsedMilliseconds =
        duration<double, milli>(end - start).count();

    return metrics;
}

SortMetrics Benchmark::insertionSort(int values[], int size) {
    SortMetrics metrics;
    auto start = steady_clock::now();

    for (int i = 1; i < size; i++) {
        int key = values[i];
        int j = i - 1;

        while (j >= 0) {
            metrics.comparisons++;

            if (values[j] > key) {
                values[j + 1] = values[j];
                metrics.swaps++; // Counts shifts, not literal swaps.
                j--;
            } else {
                break;
            }
        }

        values[j + 1] = key;
    }

    auto end = steady_clock::now();
    metrics.elapsedMilliseconds =
        duration<double, milli>(end - start).count();

    return metrics;
}

int Benchmark::linearSearch(
    const int values[], int size, int target) {

    for (int i = 0; i < size; i++) {
        if (values[i] == target) {
            return i;
        }
    }

    return -1;
}

int Benchmark::binarySearch(
    const int values[], int size, int target) {

    int left = 0;
    int right = size - 1;

    while (left <= right) {
        int middle = left + (right - left) / 2;

        if (values[middle] == target) {
            return middle;
        }

        if (values[middle] < target) {
            left = middle + 1;
        } else {
            right = middle - 1;
        }
    }

    return -1;
}

SearchMetrics Benchmark::measureLinearSearch(
    const int values[], int size, int target) {

    SearchMetrics metrics;
    auto start = steady_clock::now();

    for (int i = 0; i < size; i++) {
        metrics.comparisons++;

        if (values[i] == target) {
            metrics.index = i;
            break;
        }
    }

    auto end = steady_clock::now();
    metrics.elapsedMilliseconds =
        duration<double, milli>(end - start).count();

    return metrics;
}

SearchMetrics Benchmark::measureBinarySearch(
    const int values[], int size, int target) {

    SearchMetrics metrics;
    int left = 0;
    int right = size - 1;

    auto start = steady_clock::now();

    while (left <= right) {
        int middle = left + (right - left) / 2;
        metrics.comparisons++;

        if (values[middle] == target) {
            metrics.index = middle;
            break;
        }

        if (values[middle] < target) {
            left = middle + 1;
        } else {
            right = middle - 1;
        }
    }

    auto end = steady_clock::now();
    metrics.elapsedMilliseconds =
        duration<double, milli>(end - start).count();

    return metrics;
}

namespace {
    int* createDataset(int size, const string& pattern,
                       mt19937& generator) {
        int* values = new int[size];

        for (int i = 0; i < size; i++) {
            values[i] = i + 1;
        }

        if (pattern == "Random") {
            shuffle(values, values + size, generator);
        } else if (pattern == "Reverse Sorted") {
            reverse(values, values + size);
        }

        return values;
    }

    int* copyDataset(const int source[], int size) {
        int* copy = new int[size];

        for (int i = 0; i < size; i++) {
            copy[i] = source[i];
        }

        return copy;
    }

    bool isSorted(const int values[], int size) {
        for (int i = 1; i < size; i++) {
            if (values[i - 1] > values[i]) {
                return false;
            }
        }

        return true;
    }

    void printSortResult(const string& algorithm,
                         const string& pattern,
                         int size,
                         const SortMetrics& metrics,
                         bool sorted) {
        cout << left
             << setw(18) << algorithm
             << setw(17) << pattern
             << setw(10) << size
             << setw(16) << metrics.comparisons
             << setw(16) << metrics.swaps
             << setw(16) << fixed << setprecision(3)
             << metrics.elapsedMilliseconds
             << (sorted ? "Yes" : "NO")
             << '\n';
    }
}

void Benchmark::runFullSuite() {
    const int sizes[] = {100, 1000, 10000, 50000};

    const string patterns[] = {
        "Random",
        "Sorted",
        "Reverse Sorted"
    };

    bool runLargeQuadraticTests = false;
    char answer;

    cout << "\n============================================\n";
    cout << "       SORTING AND SEARCHING BENCHMARK\n";
    cout << "============================================\n";

    cout << "\nThe 50,000-element tests for Bubble Sort,\n";
    cout << "Selection Sort, and reverse/random Insertion\n";
    cout << "Sort may take a long time.\n";
    cout << "Run all sorting algorithms at size 50,000? (y/n): ";

    cin >> answer;

    if (answer == 'y' || answer == 'Y') {
        runLargeQuadraticTests = true;
    }

    random_device rd;
    mt19937 generator(rd());

    cout << "\nSORTING RESULTS\n";
    cout << left
         << setw(18) << "Algorithm"
         << setw(17) << "Pattern"
         << setw(10) << "Size"
         << setw(16) << "Comparisons"
         << setw(16) << "Swaps/Shifts"
         << setw(16) << "Time (ms)"
         << "Sorted?"
         << '\n';

    cout << string(105, '-') << '\n';

    for (int size : sizes) {
        for (const string& pattern : patterns) {

            if (size == 50000 &&
                !runLargeQuadraticTests) {
                cout << "Skipped quadratic sorts for 50,000 "
                     << "elements (" << pattern << ").\n";
                continue;
            }

            int* original = createDataset(
                size, pattern, generator);

            int* values = copyDataset(original, size);
            SortMetrics bubble = bubbleSort(values, size);
            printSortResult(
                "Bubble Sort", pattern, size,
                bubble, isSorted(values, size));
            delete[] values;

            values = copyDataset(original, size);
            SortMetrics selection = selectionSort(values, size);
            printSortResult(
                "Selection Sort", pattern, size,
                selection, isSorted(values, size));
            delete[] values;

            values = copyDataset(original, size);
            SortMetrics insertion = insertionSort(values, size);
            printSortResult(
                "Insertion Sort", pattern, size,
                insertion, isSorted(values, size));
            delete[] values;

            delete[] original;
        }
    }

    cout << "\nSEARCHING RESULTS\n";
    cout << left
         << setw(18) << "Algorithm"
         << setw(12) << "Size"
         << setw(16) << "Comparisons"
         << setw(16) << "Time (ms)"
         << "Found index"
         << '\n';

    cout << string(75, '-') << '\n';

    for (int size : sizes) {
        int* sortedValues = createDataset(
            size, "Sorted", generator);

        // Search for a value located near the middle.
        int target = (size + 1) / 2;

        SearchMetrics linear = measureLinearSearch(
            sortedValues, size, target);

        cout << left
             << setw(18) << "Linear Search"
             << setw(12) << size
             << setw(16) << linear.comparisons
             << setw(16) << fixed << setprecision(3)
             << linear.elapsedMilliseconds
             << linear.index << '\n';

        SearchMetrics binary = measureBinarySearch(
            sortedValues, size, target);

        cout << left
             << setw(18) << "Binary Search"
             << setw(12) << size
             << setw(16) << binary.comparisons
             << setw(16) << fixed << setprecision(3)
             << binary.elapsedMilliseconds
             << binary.index << '\n';

        delete[] sortedValues;
    }

    cout << "\nBenchmark complete.\n";
    cout << "Note: Insertion Sort's swaps/shifts column counts "
         << "element shifts, not literal swaps.\n";
}