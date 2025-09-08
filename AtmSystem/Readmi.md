

---

# ATM System

## Overview

The **ATM System** is a professional console-based application in C++ that simulates a real-world ATM. It is designed to **interact seamlessly with the shared client database** (`Clients.txt`) used by the Bank System, ensuring **real-time synchronization** of client information.

This system allows clients to securely **withdraw, deposit, check balance, and edit account information**, providing a realistic banking experience.

---

## Features

* **Secure Login:** Authenticate using account number and PIN.
* **Quick Withdraw:** Withdraw preset amounts (20, 50, 100, …, 1000).
* **Normal Withdraw:** Enter a custom amount (must be multiple of 5).
* **Deposit:** Add funds to the account with confirmation prompt.
* **Check Balance:** View current account balance.
* **Edit Account Info:** Change Name, PIN, or Phone Number.
* **Real-Time Updates:** All changes immediately reflect in the shared database.

---

## Code Quality & Design

* **Functional Programming Approach:** Each operation (withdraw, deposit, edit) is encapsulated in **reusable functions**.
* **Structs & Vectors:** Efficient dynamic storage of clients in memory.
* **File I/O:** Persistent database with update and delete support.
* **Modular & Maintainable:**

  * Clear separation of menu screens and functionality.
  * Readable function and variable names for easier understanding.
  * Designed for **easy maintenance, extension, and debugging**.
* **Input Validation & Security:** Checks for invalid inputs and ensures transactions do not exceed available balance.

---

## How It Works

1. **Login Screen:** Users enter account number and PIN.
2. **Main Menu:** Provides access to all features.
3. **Functional Operations:** Each operation is executed via dedicated functions.
4. **Database Interaction:** All modifications are written back to the shared file for **synchronized updates**.

---

## Example User Interaction

### **Login**

```
----------------------------------
        Login Screen
----------------------------------
Enter Account Number? 10003
Enter Pin? 9876
```

### **Main Menu**

```
=============================================
        ATM Main Menu Screen
=============================================
[1] Quick Withdraw
[2] Normal Withdraw
[3] Deposit
[4] Check Balance
[5] Edit Account Info
[6] Logout
=============================================
Hello John Doe, Welcome To ATM System :)
Enter your choice:
```

### **Quick Withdraw**

```
===============================================
        Quick Withdraw Screen
===============================================
[1] 20     [2] 50
[3] 100    [4] 200
[5] 400    [6] 600
[7] 800    [8] 1000
[9] Exit
===============================================
Your Balance is: 1500.75
Enter your choice:
```

### **Deposit**

```
=======================================
        Deposit Screen
=======================================
Enter a Positive Deposit Amount ? 300
Are you sure you want to perform this transaction? (y/n) ? y

Done successfully, New Balance = 1800.75
```

### **Edit Account Info**

```
==============================================
        Edit Account Information
==============================================
[1] Show Account Information
[2] Change Name
[3] Change PIN
[4] Change Phone Number
[5] Main Menu
==============================================
Enter your choice: 1

The following is the extracted client record :
Account Number : 10003
Pin Code       : 9876
Name           : John Doe
Phone          : 555-0303
Account Balance: 4500
```

---

## Lessons & Techniques Used

* **Functional programming**: Clear, reusable functions for each ATM operation.
* **Structs & Vectors**: Efficient data representation and dynamic memory handling.
* **File I/O**: Reading/writing clients to a persistent file.
* **Input validation & logical flow**: Prevents errors and ensures smooth operation.
* **Modular design**: Menu screens and functional code are separated for clarity.
* **Clean & readable code**: Meaningful names allow for easy understanding, maintenance, and scalability.

---

## Integration with Bank System

* **Shared database (`Clients.txt`)** ensures real-time synchronization.
* Any changes in the ATM system (deposit, withdraw, edit info) are reflected in the Bank System immediately.
* Designed for **easy extension**, such as adding new ATM operations or connecting with a GUI later.

---

