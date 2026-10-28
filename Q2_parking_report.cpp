/*
 * Name       : Muhammad Harmain
 * Reg No     : L1S26BSCSC0079
 * Assignment : 02 - File Handling
 * Question   : Q2 - Parking Report
 */

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

int main() {
    ifstream inFile("parking.txt");
    if (!inFile) {
        cout << "parking.txt not found!" << endl;
        return 1;
    }

    int d, m, y;
    char slash;
    // Read date (e.g., 09/10/2026)
    inFile >> d >> slash >> m >> slash >> y;

    // Skip the rest of the date line and the header line
    inFile.ignore(100, '\n');
    inFile.ignore(100, '\n');

    char plate[15];
    char type;
    int inH, inM, outH, outM;
    char colon;

    int vehicles = 0, cars = 0, bikes = 0;
    int totalCollected = 0;
    int maxMinutes = -1;
    char longestPlate[15] = "";
    int longestH = 0, longestM = 0;

    ofstream receipts("receipts.txt");
    receipts << "Receipts for " << d << "/" << m << "/" << y << endl;

    // Read vehicle lines one by one
    while (inFile >> plate >> type >> inH >> colon >> inM >> outH >> colon >> outM) {
        vehicles++;
        if (type == 'C') cars++;
        else if (type == 'B') bikes++;

        int inTotalMins = inH * 60 + inM;
        int outTotalMins = outH * 60 + outM;
        int parkedMins = outTotalMins - inTotalMins;

        int hoursCharged = (parkedMins + 59) / 60;
        if (hoursCharged == 0) {
            hoursCharged = 1;
        }

        int fee = 0;
        if (type == 'C') {
            fee = hoursCharged * 100;
        }
        else if (type == 'B') {
            fee = hoursCharged * 40;
        }

        totalCollected += fee;

        int hPart = parkedMins / 60;
        int mPart = parkedMins % 60;

        cout << plate << " ";
        if (type == 'C') cout << "Car ";
        else cout << "Bike ";
        cout << hPart << " h " << mPart << " min Fee: " << fee << endl;

        receipts << plate << " " << fee << endl;

        if (parkedMins > maxMinutes) {
            maxMinutes = parkedMins;
            strcpy(longestPlate, plate);
            longestH = hPart;
            longestM = mPart;
        }
    }

    inFile.close();
    receipts.close();

    if (vehicles == 0) {
        cout << "First Parking report for " << d << "/" << m << "/" << y << ", then No vehicles found!" << endl; // Or check specific requirement
        return 0;
    }

    cout << "Parking report for " << d << "/" << m << "/" << y << endl;
    // Re-print report items or structure as required. Wait, the loop already printed individual vehicle lines!
    // Let's print the summary lines:
    cout << "Vehicles: " << vehicles << endl;
    cout << "Cars: " << cars <<"  Bikes: " << bikes << endl; // wait, formatted below correctly
        cout << "Cars: " << cars << " Bikes: " << bikes << endl;
    cout << "Total collected: " << totalCollected << endl;
    cout << "Longest stay: " << longestPlate << " (" << longestH << " h " << longestM << " min)" << endl;

    return 0;
}