/*
 * Name       : Muhammad Harmain
 * Reg No     : L1S26BSCS0079
 * Assignment : 02 - File Handling
 * Question   : Q5 - Expense Tracker
 */

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

void showMenu() {
    cout << "===== Expense Tracker =====" << endl;
    cout << "1. Add an expense" << endl;
    cout << "2. Show all expenses" << endl;
    cout << "3. Show total of a category" << endl;
    cout << "4. Clear all expenses" << endl;
    cout << "5. Exit" << endl;
    cout << "Enter your choice: ";
}

int main() {
    int choice;
    do {
        showMenu();
        if (!(cin >> choice)) {
            break;
        }

        if (choice == 1) {
            char category[20];
            int amount;
            cout << "Enter category: ";
            cin >> category;
            cout << "Enter amount: ";
            cin >> amount;

            if (amount <= 0) {
                cout << "Invalid amount!" << endl;
            }
            else {
                ofstream outFile("expenses.txt", ios::app);
                outFile << category << " " << amount << endl;
                outFile.close();
                cout << "Expense saved." << endl;
            }
        }
        else if (choice == 2) {
            ifstream inFile("expenses.txt");
            if (!inFile) {
                cout << "No expenses yet." << endl;
            }
            else {
                char category[20];
                int amount;
                int n = 1;
                int totalSpent = 0;
                int maxAmount = -1;
                char largestCat[20] = "";
                bool hasData = false;

                while (inFile >> category >> amount) {
                    hasData = true;
                    cout << n << ". " << category << " " << amount << endl;
                    totalSpent += amount;

                    if (amount > maxAmount) {
                        maxAmount = amount;
                        strcpy(largestCat, category);
                    }
                    n++;
                }
                inFile.close();

                if (!hasData) {
                    cout << "No expenses yet." << endl;
                }
                else {
                    cout << "Total spent: " << totalSpent << endl;
                    cout << "Largest expense: " << largestCat << " (" << maxAmount << ")" << endl;
                }
            }
        }
        else if (choice == 3) {
            char targetCat[20];
            cout << "Enter category: ";
            cin >> targetCat;

            ifstream inFile("expenses.txt");
            if (!inFile) {
                cout << "No expenses found for " << targetCat << endl;
            }
            else {
                char category[20];
                int amount;
                int count = 0;
                int totalCat = 0;

                while (inFile >> category >> amount) {
                    if (strcmp(category, targetCat) == 0) {
                        count++;
                        totalCat += amount;
                    }
                }
                inFile.close();

                if (count == 0) {
                    cout << "No expenses found for " << targetCat << endl;
                }
                else {
                    cout << "Expenses in " << targetCat << ": " << count << endl;
                    cout << "Total for " << targetCat << ": " << totalCat << endl;
                }
            }
        }
        else if (choice == 4) {
            ofstream outFile("expenses.txt"); // Plain ofstream clears the file
            outFile.close();
            cout << "All expenses cleared." << endl;
        }
        else if (choice == 5) {
            cout << "Goodbye!" << endl;
        }
        else {
            cout << "Invalid choice!" << endl;
        }

        cout << endl;
    } while (choice != 5);

    return 0;
}