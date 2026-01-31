
/**
 * File: Student.h
 * Description: Defines the data structure representing a Student.
 * Implements operator overloading to facilitate direct object comparison.
 */

#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <string>
#include <iomanip> // For output formatting

using namespace std;

struct Student {
    string id;          // Primary key (e.g., "SE201640")
    string fullName;    // Payload data (increases swap cost compared to simple integers)
    float gpa;          // Sorting criterion

    // Constructor
    Student(string _id = "", string _name = "", float _gpa = 0.0)
        : id(_id), fullName(_name), gpa(_gpa) {}

    // --- CORE TECHNIQUE: OPERATOR OVERLOADING ---
    // Why: Allows sorting algorithms to compare two Student objects naturally
    // using the '<' and '>' operators, just like integers.

    // Overload '<' operator for ascending sort
    bool operator<(const Student& other) const {
        // Primary sort key: GPA
        if (gpa != other.gpa)
            return gpa < other.gpa;
        // Secondary sort key: ID (to ensure stability if GPAs are equal)
        return id < other.id;
    }

    // Overload '>' operator
    bool operator>(const Student& other) const {
        if (gpa != other.gpa)
            return gpa > other.gpa;
        return id > other.id;
    }

    // Helper function to display student info (useful for debugging)
    void print() const {
        cout << left << setw(10) << id
             << left << setw(25) << fullName
             << left << setw(5) << fixed << setprecision(2) << gpa << endl;
    }
};

#endif
