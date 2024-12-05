#include "User.h"
#include <iostream>
#include <iomanip>
#include <algorithm>

User::User(const std::string& username, double balance) : username(username), balance(balance) {}

void User::tradingMenu(std::vector<Stock>& stocks) {
    int choice;
    do {
        std::cout << "\nTrading Menu:\n";
        std::cout << "1. View Available Stocks\n";
        std::cout << "2. Buy Stocks\n";
        std::cout << "3. Sell Stocks\n";
        std::cout << "4. View Portfolio\n";
        std::cout << "5. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                for (const auto& stock : stocks) {
                    std::cout << stock.getSymbol() << " - " << stock.getCurrentPrice() << std::endl;
                }
                break;
            case 2:
                buyStock(stocks);
                break;
            case 3:
                sellStock();
                break;
            case 4:
                viewPortfolio();
                break;
            case 5:
                std::cout << "Exiting trading menu.\n";
                break;
            default:
                std::cout << "Invalid choice!\n";
        }
    } while (choice != 5);
}

void User::buyStock(std::vector<Stock>& stocks) {
    std::string symbol;
    int quantity;
    std::cout << "Enter the stock symbol to buy: ";
    std::cin >> symbol;
    std::cout << "Enter quantity to buy: ";
    std::cin >> quantity;

    auto it = std::find_if(stocks.begin(), stocks.end(), [&](const Stock& stock) {
        return stock.getSymbol() == symbol;
    });

    if (it != stocks.end()) {
        double cost = it->getCurrentPrice() * quantity;
        if (balance >= cost) {
            balance -= cost;
            portfolio.emplace_back(*it, quantity);
            std::cout << "Stock purchased successfully.\n";
        } else {
            std::cout << "Insufficient balance.\n";
        }
    } else {
        std::cout << "Stock not found.\n";
    }
}

void User::sellStock() {
    std::string symbol;
    int quantity;
    std::cout << "Enter the stock symbol to sell: ";
    std::cin >> symbol;
    std::cout << "Enter quantity to sell: ";
    std::cin >> quantity;

    auto it = std::find_if(portfolio.begin(), portfolio.end(), [&](const std::pair<Stock, int>& p) {
        return p.first.getSymbol() == symbol;
    });

    if (it != portfolio.end()) {
        if (it->second >= quantity) {
            balance += it->first.getCurrentPrice() * quantity;
            it->second -= quantity;
            if (it->second == 0) portfolio.erase(it);
            std::cout << "Stock sold successfully.\n";
        } else {
            std::cout << "Insufficient quantity to sell.\n";
        }
    } else {
        std::cout << "You do not own this stock.\n";
    }
}

void User::viewPortfolio() const {
    std::cout << "\nPortfolio:\n";
    for (const auto& p : portfolio) {
        std::cout << p.first.getSymbol() << " - " << p.second << " shares @ " << p.first.getCurrentPrice() << std::endl;
    }
    std::cout << "Balance: " << balance << std::endl;
}

