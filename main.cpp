/**
 * File: main.cpp
 * Description: The main driver for the sorting algorithm research.
 * Orchestrates the data generation, algorithm execution, time measurement,
 * validation, and result logging.
 */

#include <iostream>
#include <vector>
#include <chrono> // For high-precision timing
#include "Student.h"
#include "DataGenerator.h"
#include "SortAlgorithms.h"
#include "FileLogger.h"

using namespace std;
using namespace std::chrono;

// Structure to hold algorithm metadata
struct AlgoRunner {
    string name;
    void (*func)(vector<Student>&); // Function pointer to the sorting algorithm
    bool skipOnLargeData;           // Flag to skip O(n^2) algorithms on large datasets
};

// Function: runExperiment
// Description: Runs all algorithms for a specific dataset size and scenario.
void runExperiment(int N, string scenarioName, vector<Student> data, FileLogger& logger) {

    // Define the list of algorithms to test
    vector<AlgoRunner> algorithms = {
        {"Bubble Sort", SortAlgorithms::bubbleSort, true},       // O(n^2) - Slow
        {"Insertion Sort", SortAlgorithms::insertionSort, true}, // O(n^2) - Slow (except nearly sorted)
        {"Quick Sort", SortAlgorithms::quickSort, false},        // O(n log n) - Fast
        {"C++ Std Sort", SortAlgorithms::cppStandardSort, false} // O(n log n) - Optimized
    };

    for (auto& algo : algorithms) {
        // SAFETY CHECK: Skip slow algorithms on large datasets (>20k)
        // Exception: Insertion Sort is allowed for "Nearly Sorted" scenario
        if (algo.skipOnLargeData && N > 20000 && scenarioName != "Nearly Sorted") {
            cout << "   [Skip] " << left << setw(15) << algo.name << " (Too slow for large N)" << endl;
            continue;
        }

        // CLONE DATA: Essential to ensure every algorithm works on the same unsorted input
        vector<Student> dataCopy = data;

        // MEASURE TIME
        auto start = high_resolution_clock::now();
        algo.func(dataCopy); // Execute Sort
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);

        // VALIDATION: Verify if the data is actually sorted
        if (!SortAlgorithms::isSorted(dataCopy)) {
            cerr << "   [ERROR] " << algo.name << " failed to sort correctly!" << endl;
        } else {
            // LOGGING: Write to CSV and Console
            logger.logResult(N, scenarioName, algo.name, duration.count());
            cout << "   [Done] " << left << setw(15) << algo.name
                 << ": " << duration.count() << " us" << endl;
        }
    }
}

int main() {
    DataGenerator gen;
    string outputFilename = "research_results.csv";
    FileLogger logger(outputFilename);

    // Experimental Parameters
    // We test with N = 1000 up to 100,000 students
    vector<int> datasetSizes = {1000, 10000, 30000, 50000, 100000};

    cout << "==========================================================" << endl;
    cout << "   RESEARCH PROJECT: SORTING ALGORITHMS PERFORMANCE EVALUATION" << endl;
    cout << "   Target Object: Student Records" << endl;
    cout << "==========================================================\n" << endl;

    for (int N : datasetSizes) {
        cout << ">>> DATASET SIZE: N = " << N << " Students" << endl;

        // SCENARIO 1: Random Data
        cout << "   + Scenario: Random Distribution" << endl;
        runExperiment(N, "Random", gen.generateRandomList(N), logger);

        // SCENARIO 2: Nearly Sorted Data (Expect Insertion Sort to perform well)
        cout << "   + Scenario: Nearly Sorted" << endl;
        runExperiment(N, "Nearly Sorted", gen.generateNearlySortedList(N), logger);

        // SCENARIO 3: Reverse Sorted Data (Stress test)
        cout << "   + Scenario: Reverse Sorted" << endl;
        runExperiment(N, "Reverse Sorted", gen.generateReverseList(N), logger);

        cout << "----------------------------------------------------------" << endl;
    }

    cout << "\n[COMPLETED] Experiment finished successfully." << endl;
    cout << "Results saved to '" << outputFilename << "'. Please use Excel/Python to plot the data." << endl;

    return 0;
}
