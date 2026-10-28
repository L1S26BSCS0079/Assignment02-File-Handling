/*
 * Name       : Muhammad Harmain
 * Reg No     : L1S26BSCS0079
 * Assignment : 02 - File Handling
 * Question   : Q3 - Scholarship List
 */

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

int main() {
    char path[100];
    cout << "Enter the file name: ";
    cin.getline(path, 100);

    ifstream inFile(path);
    if (!inFile.is_open()) {
        cout << "Could not open " << path << "!" << endl;
        return 1;
    }

    int n;
    inFile >> n;
    inFile.ignore(100, '\n');

    if (n > 30) {
        cout << "Too many students!" << endl;
        inFile.close();
        return 0;
    }

    ofstream scholarship("scholarship.txt");

    char name[30];
    double cgpa;
    int count = 0;
    double totalCgpa = 0;
    int eligibleCount = 0;
    double maxCgpa = -1.0;
    char topStudent[30] = "";
    double topCgpa = 0;

    int readRecords = 0;
    for (int i = 0; i < n; i++) {
        if (!inFile.getline(name, 30, ',')) {
            break;
        }
        if (!(inFile >> cgpa)) {
            break;
        }
        inFile.ignore(100, '\n');

        readRecords++;
        count++;
        totalCgpa += cgpa;

        cout << "[" << name << "] CGPA: " << cgpa << endl;

        if (cgpa >= 3.50) {
            eligibleCount++;
            scholarship << name << "," << cgpa << endl;
        }

        if (cgpa > maxCgpa) {
            maxCgpa = cgpa;
            strcpy(topStudent, name);
            topCgpa = cgpa;
        }
    }

    inFile.close();
    scholarship.close();

    if (readRecords < n) {
        cout << "Warning: only " << readRecords << " of " << n << " records found." << endl;
    }

    if (count == 0) {
        cout << "No students found!" << endl;
        return 0;
    }

    cout << "Students: " << count << endl;
    cout << "Average CGPA: " << (totalCgpa / count) << endl;
    cout << "Eligible for scholarship: " << eligibleCount << endl;
    cout << "Top student: " << topStudent << " (" << topCgpa << ")" << endl;

    return 0;
}