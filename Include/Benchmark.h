#ifndef BENCHMARK_H
#define BENCHMARK_H

struct SortMetrics {
    long long comparisons;
    long long swaps;
    double elapsedMilliseconds;

    SortMetrics()
        : comparisons(0), swaps(0), elapsedMilliseconds(0.0) {}
};

struct SearchMetrics {
    long long comparisons;
    double elapsedMilliseconds;
    int index;

    SearchMetrics()
        : comparisons(0), elapsedMilliseconds(0.0), index(-1) {}
};

class Benchmark {
public:
    static SortMetrics bubbleSort(int values[], int size);
    static SortMetrics selectionSort(int values[], int size);
    static SortMetrics insertionSort(int values[], int size);

    static int linearSearch(const int values[], int size, int target);
    static int binarySearch(const int values[], int size, int target);

    static SearchMetrics measureLinearSearch(
        const int values[], int size, int target);

    static SearchMetrics measureBinarySearch(
        const int values[], int size, int target);

    static void runFullSuite();
};

#endif