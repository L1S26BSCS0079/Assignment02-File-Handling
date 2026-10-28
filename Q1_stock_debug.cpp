/*
 * Name       : Muhammad Harmain
 * Reg No     : L1S26BSCS0079
 * Assignment : 02 - File Handling
 * Question   : Q1 - Stock Report (Debugging)
 */

 // FIX 1: <fstream> header was missing so ifstream and ofstream were unknown
#include <fstream>
#include <iostream>
using namespace std;

int main() {
    ifstream inFile("stock.txt");

    // FIX 2: Corrected the condition to check if the file failed to open (!inFile)
    if (!inFile) {
        cout << "stock.txt not found!" << endl;
        return 1;
    }

    // FIX 3: Added ios::app so that existing lines in reorder.txt are kept and not overwritten
    ofstream reorder("reorder.txt", ios::app);

    // FIX 4: Added ignore to skip the first header line of stock.txt
    inFile.ignore(100, '\n');

    char code[10];
    int qty, count = 0, low = 0;
    double price;

    // FIX 5: Changed total from int to double to properly handle decimal values in stock calculation
    double total = 0;

    while (count < 50 && inFile >> code >> qty >> price) {
        count++;
        total = total + qty * price;
        if (qty < 10) {
            reorder << code << " " << qty << endl; // FIX 6: Added endl to write each low stock item on a new line
            low++;
        }
    }
    inFile.close();
    reorder.close();

    cout << "Items: " << count << endl;
    cout << "Total stock value: " << total << endl;
    cout << "Low stock items: " << low << endl;
    return 0;
}