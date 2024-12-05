#include "Stock.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>

#ifdef _WIN32
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
int _kbhit() {
    struct termios oldt, newt;
    int ch;
    int oldf;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);
    if (ch != EOF) {
        ungetc(ch, stdin);
        return 1;
    }
    return 0;
}
#endif

using namespace std;

void moveCursorTo(int row, int col) {
    cout << "\033[" << row << ";" << col << "H";
}

void clearLine(int row) {
    moveCursorTo(row, 1);
    cout << "\033[K";
}

void setColor(int color) {
    switch (color) {
        case 1: cout << "\033[31m"; break;  // Red
        case 2: cout << "\033[32m"; break;  // Green
        case 0: cout << "\033[0m"; break;   // Reset to default
    }
}

bool safeStod(const string& str, double& result) {
    try {
        result = stod(str);
        return true;
    } catch (const invalid_argument&) {
        return false;
    }
}

void displayTableHeader() {
    moveCursorTo(1, 1);
    cout << left << setw(15) << "Symbol"
         << right << setw(15) << "Opening Price"
         << setw(20) << "Current Price"
         << setw(15) << "High Price"
         << setw(15) << "Low Price" << endl;
    moveCursorTo(2, 1);
    cout << string(80, '-') << endl;
}

void displayStockData(vector<Stock>& stocks) {
    srand(static_cast<unsigned>(time(0)));

    ifstream file("stocks.csv");
    if (!file.is_open()) {
        cout << "Failed to open file!" << endl;
        return;
    }

    vector<Stock> stocksData;
    string line;
    getline(file, line);  // Skip header

    while (getline(file, line)) {
        stringstream ss(line);
        string temp;
        string symbol;
        double openingPrice, highPrice, lowPrice;

        getline(ss, symbol, ',');   // Read symbol
        for (int i = 1; i < 4; ++i) getline(ss, temp, ',');  // Skip unnecessary columns
        if (!safeStod(temp, openingPrice)) continue;

        for (int i = 1; i < 3; ++i) getline(ss, temp, ',');  // Skip columns
        if (!safeStod(temp, highPrice)) continue;

        getline(ss, temp, ',');  // Low Price
        if (!safeStod(temp, lowPrice)) continue;

        stocksData.push_back(Stock(symbol, openingPrice, highPrice, lowPrice));
    }
    file.close();

    displayTableHeader();

    while (true) {
        int row = 3;
        for (auto& stock : stocksData) {
            clearLine(row);
            moveCursorTo(row, 1);

            double newPrice = stock.getFluctuatingPrice(2.0);
            double priceChange = newPrice - stock.lastPrice;
            stock.lastPrice = newPrice;

            if (newPrice > stock.highPrice) stock.highPrice = newPrice;
            if (newPrice < stock.lowPrice) stock.lowPrice = newPrice;

            cout << left << setw(15) << stock.symbol
                 << right << setw(15) << fixed << setprecision(2) << stock.openingPrice;

            if (priceChange > 0) {
                setColor(2);  // Green
                cout << setw(20) << "↑ " + to_string(newPrice);
            } else if (priceChange < 0) {
                setColor(1);  // Red
                cout << setw(20) << "↓ " + to_string(newPrice);
            } else {
                setColor(0);  // Default
                cout << setw(20) << newPrice;
            }

            setColor(0);  // Reset color
            cout << setw(15) << fixed << setprecision(2) << stock.highPrice
                 << setw(15) << stock.lowPrice;
            row++;
        }

        cout.flush();
        std::this_thread::sleep_for(chrono::seconds(3));

        if (_kbhit()) {
            char ch = getchar();
            if (ch == 'q' || ch == 'Q') break;
        }
    }
}

