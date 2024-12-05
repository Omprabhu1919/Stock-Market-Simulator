# Stock Market Simulator

Welcome to the Stock Market Simulator! This C++ project allows users to simulate stock trading by buying and selling stocks, managing their portfolio, and viewing transaction history. It uses real-time stock price updates and ensures data persistence through file storage.

> **Note:** This project is a work in progress. Some features may not be fully implemented, and we are actively working to enhance its functionality.

## Features
- **Real-Time Stock Updates**  
  Stock prices fluctuate dynamically during the simulation.
  
- **Portfolio Management**  
  Users can manage their holdings, track unrealized profits/losses, and make informed trading decisions.

- **Trading System**  
  - **Buy Stocks**: Purchase stocks based on live prices.  
  - **Sell Stocks**: Liquidate holdings to realize profits or minimize losses.

- **Transaction History**  
  A complete log of all trades is stored and accessible for review.

- **Persistent Data**  
  User portfolio and transaction history are stored in the `stocks.csv` file for continuity across sessions.

## Project Structure
### Source Files
- **`main.cpp`**  
  The entry point of the application. Handles the menu-driven interface for the simulator, allowing users to buy/sell stocks, view portfolios, and access transaction history.

- **`Stock.cpp`**  
  Implements the `Stock` class, including attributes for stock symbol, prices (opening and last), and methods for real-time price fluctuation.

- **`Stock.h`**  
  The header file for the `Stock` class, defining its structure and behavior.

- **`StockDisplay.cpp`**  
  Manages the real-time display of stock price fluctuations in a separate terminal window.

- **`User.cpp`**  
  Implements the `User` class, including methods for managing the portfolio, performing trades, and accessing the transaction history.

- **`User.h`**  
  The header file for the `User` class, defining its structure and available operations.

### Supporting Files
- **`stocks.csv`**  
  Stores persistent data about stocks, the user's portfolio, and transaction history. Ensures that data is not lost between sessions.

- **`stock_simulator`**  
  The compiled binary of the program.

## Installation and Setup
1. Clone the repository:
   ```bash
   git clone https://github.com/your-repo/stock-market-simulator.git
