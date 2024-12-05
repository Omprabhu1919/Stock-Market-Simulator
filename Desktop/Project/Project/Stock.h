#ifndef STOCK_H
#define STOCK_H

#include <string>
#include <vector>
#include <iostream>

class Stock {
public:
    std::string symbol;
    double openingPrice;
    double lastPrice;
    double highPrice;
    double lowPrice;

    // Constructor
    Stock(const std::string& symbol, double openingPrice, double highPrice, double lowPrice)
        : symbol(symbol), openingPrice(openingPrice), lastPrice(openingPrice), highPrice(highPrice), lowPrice(lowPrice) {}

    // Function to get the price fluctuation within bounds
    double getFluctuatingPrice(double fluctuationPercent) {
        double fluctuation = (rand() / (RAND_MAX / (fluctuationPercent * 2.0))) - fluctuationPercent;
        return lastPrice * (1.0 + fluctuation / 100.0);
    }
};

#endif

