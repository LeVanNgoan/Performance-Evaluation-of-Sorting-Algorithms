/**
 * File: SortAlgorithms.h
 * Description: Implementation of various sorting algorithms.
 * Includes: Bubble Sort, Insertion Sort, Quick Sort (Middle Pivot), and C++ Standard Sort.
 */

#ifndef SORTALGORITHMS_H
#define SORTALGORITHMS_H

#include "Student.h"
#include <vector>
#include <algorithm>

class SortAlgorithms {
public:
    // --- 1. BUBBLE SORT ---
    // Complexity: O(n^2)
    // Strategy: Repeatedly steps through the list, compares adjacent elements and swaps them.
    static void bubbleSort(vector<Student>& list) {
        int n = list.size();
        for (int i = 0; i < n - 1; i++) {
            bool swapped = false; // Optimization flag
            for (int j = 0; j < n - i - 1; j++) {
                if (list[j] > list[j + 1]) {
                    swap(list[j], list[j + 1]);
                    swapped = true;
                }
            }
            // If no elements were swapped, the list is already sorted.
            if (!swapped) break;
        }
    }

    // --- 2. INSERTION SORT ---
    // Complexity: O(n^2) average, but O(n) for nearly sorted data.
    // Strategy: Builds the sorted array one item at a time.
    static void insertionSort(vector<Student>& list) {
        int n = list.size();
        for (int i = 1; i < n; i++) {
            Student key = list[i];
            int j = i - 1;
            // Move elements of list[0..i-1] that are greater than key
            // to one position ahead of their current position
            while (j >= 0 && list[j] > key) {
                list[j + 1] = list[j];
                j = j - 1;
            }
            list[j + 1] = key;
        }
    }

    // --- 3. QUICK SORT (Optimized with Middle Pivot) ---
    // Complexity: O(n log n) average.
    // Strategy: Divide and Conquer.
    static int partition(vector<Student>& list, int low, int high) {
        // Selection of Middle Pivot prevents worst-case O(n^2) on sorted arrays
        Student pivot = list[low + (high - low) / 2];
        int i = low;
        int j = high;

        while (i <= j) {
            while (list[i] < pivot) i++;
            while (list[j] > pivot) j--;
            if (i <= j) {
                swap(list[i], list[j]);
                i++;
                j--;
            }
        }
        return i;
    }

    static void quickSortRecursive(vector<Student>& list, int low, int high) {
        if (low < high) {
            int pi = partition(list, low, high);
            if (low < pi - 1) quickSortRecursive(list, low, pi - 1);
            if (pi < high) quickSortRecursive(list, pi, high);
        }
    }

    static void quickSort(vector<Student>& list) {
        if (list.empty()) return;
        quickSortRecursive(list, 0, list.size() - 1);
    }

    // --- 4. C++ STANDARD SORT ---
    // Complexity: O(n log n). Usually Introsort (Hybrid of QuickSort, HeapSort, InsertionSort).
    // Used as the "Gold Standard" for performance comparison.
    static void cppStandardSort(vector<Student>& list) {
        sort(list.begin(), list.end());
    }

    // --- VALIDATION UTILITY ---
    // Description: Verifies if the list is correctly sorted in ascending order.
    // Crucial for scientific integrity.
    static bool isSorted(const vector<Student>& list) {
        for (size_t i = 0; i < list.size() - 1; i++) {
            if (list[i] > list[i + 1]) return false; // Found an inversion
        }
        return true;
    }
};

#endif
