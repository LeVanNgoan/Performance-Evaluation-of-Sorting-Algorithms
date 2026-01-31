/**
 * File: FileLogger.h
 * Description: Handles file I/O operations.
 * Exports experimental results to a CSV file for analysis in Excel/Python.
 */

#ifndef FILELOGGER_H
#define FILELOGGER_H

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class FileLogger {
private:
    string filename;

public:
    // Constructor: Initializes the file and writes the CSV header
    FileLogger(string _filename) : filename(_filename) {
        // ios::trunc -> Clears the file content if it already exists
        ofstream file(filename, ios::out | ios::trunc);
        if (file.is_open()) {
            file << "DatasetSize(N),Scenario,Algorithm,Time(us)\n";
            file.close();
        }
    }

    // Appends a single result row to the CSV file
    void logResult(int n, string scenario, string algoName, long long timeDuration) {
        // ios::app -> Append mode
        ofstream file(filename, ios::out | ios::app);
        if (file.is_open()) {
            file << n << ","
                 << scenario << ","
                 << algoName << ","
                 << timeDuration << "\n";
            file.close();
        } else {
            cerr << "[Error] Unable to open file for writing!" << endl;
        }
    }
};

#endif
