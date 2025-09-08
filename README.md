
---

# **Banking & ATM System Projects**

## **Project Overview**

This repository contains two related C++ console-based projects:

1. **Banking System Project**
2. **ATM System Project**

Both projects focus on **client account management, transactions, and user authentication**, providing a foundation for learning **modular programming, file handling, and role-based access control**.

---

## **1. Banking System Project**

### **Purpose**

The banking system allows administrators and authorized users to manage clients, handle transactions, and manage users with specific permissions.

### **Key Functionalities**

* **User Authentication:** Login using username and password.
* **Main Menu:** Access client management, transactions, and user management.
* **Client Management:** Add, update, delete, and find clients.
* **Transactions:** Deposit, withdraw, and view total balances.
* **User Management:** Admin can add, update, delete, and view users.

### **Screens**

* **Login Screen**

```
Login Screen
Enter User Name: 
Enter Password:
```

* **Main Menu Screen**

```
1. Show Client List
2. Add New Client
3. Delete Client
4. Update Client Info
5. Find Client
6. Transactions
7. Manage Users
8. Logout
9. Exit
```

* **Transactions Menu**

```
1. Deposit
2. Withdraw
3. Total Balance
4. Main Menu
```

* **Manage Users (Admin only)**

```
1. List Users
2. Add New User
3. Delete User
4. Update User
5. Find User
6. Main Menu
```

* **Client & User Details**

```
Client Example:
Account Number: 10001
Pin Code: 1234
Name: Ali Knj
Phone: 555-0101
Account Balance: 5000

User Example:
User Name: Admin
Password: 12345
Permissions: -1 (Full Access)
```

### **Permissions**

| Permission       | Bit Value |
| ---------------- | --------- |
| Show Client List | 1         |
| Add New Client   | 2         |
| Delete Client    | 4         |
| Update Client    | 8         |
| Find Client      | 16        |
| Transactions     | 32        |
| Manage Users     | 64        |
| Full Access      | -1        |

---

## **2. ATM System Project**

### **Purpose**

The ATM project simulates a real-world ATM interface for clients to perform **banking operations independently**, without administrator intervention.

### **Key Functionalities**

* **Quick Withdraw:** Withdraw preset amounts quickly.
* **Normal Withdraw:** Custom amount withdrawals.
* **Deposit:** Add funds to the account.
* **Check Balance:** View current account balance.
* **Logout:** Secure exit from the system.

### **Screens**

* **ATM Login Screen**

```
Enter Account Number:
Enter PIN:
```

* **ATM Main Menu**

```
1. Quick Withdraw
2. Normal Withdraw
3. Deposit
4. Check Balance
5. Logout
```

* **Quick Withdraw Options**

```
1. 20$
2. 50$
3. 100$
4. 200$
5. Main Menu
```

* **Balance Display**

```
Current Balance: 5000$
```

---

## **Code Structure & Features (Both Projects)**

* **Clean & Readable Code:** Clear variable names, modular functions.
* **File Handling:** Data persistence with text files (`Clients.txt`, `Users.txt`).
* **Modular Design:** Each feature has a dedicated function.
* **Reusability:** Functions can be reused across screens and projects.
* **Role-Based Access:** Users cannot perform actions they lack permission for.
* **Bitwise Permissions:** Efficient and scalable permission handling.
* **Error Handling:** Validates user input, prevents duplicates, ensures correct transaction limits.

---

## **Sample Data**

### Clients.txt

```
10001#//#1234#//#Ali Knj#//#555-0101#//#5000
10002#//#5678#//#Sara Ali#//#555-0202#//#3200
10003#//#9876#//#John Doe#//#555-0303#//#4500
```

### Users.txt

```
Admin#//#12345#//#-1
```

---

## **Learning Outcomes**

* Understanding **modular programming**.
* Implementing **role-based access control**.
* Practicing **file handling** and **data persistence**.
* Designing **console-based user interfaces**.
* Learning **bitwise operations for permissions**.
* Writing **clean, maintainable, and reusable code**.

---


