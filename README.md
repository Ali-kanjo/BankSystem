
# C++ Bank Client Management System

This project is a command-line interface (CLI) application built with C++ that focuses on the fundamental CRUD (Create, Read, Update, Delete) operations for managing bank clients. It serves as a foundational module for a larger banking system. All client data is persistently stored in a local text file.

## 🌟 Core Features

-   **List All Clients**: Displays a formatted table of all clients registered in the system with their details (Account Number, Name, Balance, etc.).
-   **Add a New Client**: Creates a record for a new client, ensuring the account number is unique to prevent duplicates.
-   **Update Client Information**: Searches for a client and allows for the modification of their personal or financial data.
-   **Delete a Client**: Completely removes a client's record from the system after confirmation.
-   **Find a Client**: Quickly locates and displays the information of a specific client using their account number.
-   **Data Persistence**: All client records are saved to a `Clients.txt` file to ensure data is not lost when the program closes.

## ⚙️ How It Works

The program is built around a `stClient` struct, which organizes the data for each client. On startup, the application reads the data from `Clients.txt` and loads it into an in-memory `vector`. All operations (add, update, delete) are performed on this vector, and the updated data is then written back to the file to save the changes.

## 🚀 How to Run

To run this project, you will need a C++ compiler (like G++ or the one integrated into Visual Studio).

### 1. Prerequisites
-   A C++ compiler.

### 2. Compilation & Execution (using g++)
1.  Open your terminal or Command Prompt.
2.  Navigate to the directory containing the source code file.
3.  Compile the code using the following command:
    ```sh
    g++ main.cpp -o bank_cli
    ```
4.  After a successful compilation, run the program:
    ```sh
    ./bank_cli
    ```

### Note
The program will automatically create the `Clients.txt` file in the same directory if it does not exist, which will be used to store client data.

## 📁 File Structure

```
.
├── main.cpp         # The source code file
└── Clients.txt      # The data store for clients (auto-generated)
```

Each client's data is stored on a single line within `Clients.txt`, with fields separated by the `#//#` delimiter. For example:
```
A101#//#1234#//#Adel Naji#//#555123456#//#4500.000000
A102#//#5678#//#Fatima Ali#//#555987654#//#8250.000000
```