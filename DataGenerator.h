/**
 * File: DataGenerator.h
 * Description: Generates synthetic datasets for experimental scenarios.
 * Scenarios: Random, Sorted, Reverse, and Nearly Sorted.
 */

#ifndef DATAGENERATOR_H
#define DATAGENERATOR_H

#include "Student.h"
#include <vector>
#include <random>       // C++11 Random Library
#include <algorithm>    // For std::shuffle, std::reverse

class DataGenerator {
private:
    vector<string> firstNames = {"Nguyen", "Tran", "Le", "Pham", "Hoang", "Huynh", "Phan", "Vu", "Vo", "Dang"};
    vector<string> middleNames = {"Van", "Thi", "Duc", "Minh", "Quoc", "Thanh", "Ngoc", "Tuan"};
    vector<string> lastNames = {"An", "Binh", "Cuong", "Dung", "Giang", "Hieu", "Khanh", "Linh", "Nhan", "Phuc"};

    mt19937 rng; // Mersenne Twister engine for high-quality random numbers

public:
    DataGenerator() {
        // Initialize the random seed
        random_device rd;
        rng = mt19937(rd());
    }

    // Generate a single random student
    Student generateStudent(int index) {
        string id = "SE" + to_string(200000 + index);

        // Randomize Name
        uniform_int_distribution<int> distFirst(0, firstNames.size() - 1);
        uniform_int_distribution<int> distMid(0, middleNames.size() - 1);
        uniform_int_distribution<int> distLast(0, lastNames.size() - 1);

        string name = firstNames[distFirst(rng)] + " " +
                      middleNames[distMid(rng)] + " " +
                      lastNames[distLast(rng)];

        // Randomize GPA (0.0 - 10.0)
        uniform_real_distribution<float> distGPA(0.0, 10.0);
        float gpa = distGPA(rng);

        return Student(id, name, gpa);
    }

    // SCENARIO 1: RANDOM DATA (Baseline for average case)
    vector<Student> generateRandomList(int n) {
        vector<Student> list;
        list.reserve(n); // Optimization: Reserve memory to avoid reallocations
        for (int i = 0; i < n; i++) {
            list.push_back(generateStudent(i));
        }
        return list;
    }

    // SCENARIO 2: SORTED DATA (Best case for Insertion, potentially worst for Quick)
    vector<Student> generateSortedList(int n) {
        vector<Student> list = generateRandomList(n);
        sort(list.begin(), list.end()); // Pre-sort the data
        return list;
    }

    // SCENARIO 3: REVERSE DATA (Worst case for many simple algorithms)
    vector<Student> generateReverseList(int n) {
        vector<Student> list = generateSortedList(n);
        reverse(list.begin(), list.end()); // Reverse the order
        return list;
    }

    // SCENARIO 4: NEARLY SORTED (Realistic case: updating a sorted list)
    vector<Student> generateNearlySortedList(int n) {
        vector<Student> list = generateSortedList(n);

        // Perturbation: Swap approximately 5% of the elements
        int swapCount = max(1, n / 20);
        uniform_int_distribution<int> distIndex(0, n - 1);

        for(int i = 0; i < swapCount; i++) {
            int idx1 = distIndex(rng);
            int idx2 = distIndex(rng);
            swap(list[idx1], list[idx2]);
        }
        return list;
    }
};

#endif
