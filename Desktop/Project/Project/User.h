#ifndef USER_H
#define USER_H

#include <string>
#include <vector>
#include "Stock.h"

class User {
private:
    std::string username;
    double balance;
    std::vector<std::pair<Stock, int>> portfolio; // Stock and quantity owned

public:
    User(const std::string& username, double balance);
    void tradingMenu(std::vector<Stock>& stocks);
    void buyStock(std::vector<Stock>& stocks);
    void sellStock();
    void viewPortfolio() const;
};

#endif // USER_H

