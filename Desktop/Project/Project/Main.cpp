#include <iostream>
#include <thread>
#include <cstdlib>  // For system calls
#include <chrono>   // For sleep
#include "Stock.h"  // Include StockDisplay logic

using namespace std;

// Function to launch stock display in a new terminal window
void launchStockDisplay() {
    // Open stock display in a new terminal window after user chooses to view stocks
    system("gnome-terminal -- ./stock_simulator_display");
}

int main() {
    cout << "Welcome to the Stock Market Simulator!" << endl;

    bool isRunning = true;
    while (isRunning) {
        cout << "\nMenu: \n";
        cout << "1. View Available Stocks\n";
        cout << "2. Buy Stocks\n";
        cout << "3. Sell Stocks\n";
        cout << "4. View Portfolio\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                // Launch stock display in a new terminal window
                cout << "Opening stock display...\n";
                thread displayThread(launchStockDisplay);  // Launch display in a new thread
                displayThread.detach();  // Detach to run independently
                break;
            case 2:
                cout << "Buying Stocks...\n";
                // Logic for buying stocks
                break;
            case 3:
                cout << "Selling Stocks...\n";
                // Logic for selling stocks
                break;
            case 4:
                cout << "Viewing Portfolio...\n";
                // Logic for viewing portfolio
                break;
            case 5:
                isRunning = false;
                break;
            default:
                cout << "Invalid choice, please try again.\n";
        }
    }

    cout << "Exiting the Stock Market Simulator. Goodbye!" << endl;
    return 0;
}

