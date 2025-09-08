
---

## **1️⃣ Project Overview**

The **Bank Management System** is a console-based application written in **C++** designed to manage clients, users, and financial transactions in a small banking environment.

**Key features:**

* **Client Management:** Add, update, delete, and view clients.
* **User Management:** Add, update, delete, and view system users with fine-grained permissions.
* **Transactions:** Deposit, withdraw, and view total balances.
* **Access Control:** Permission-based user system with full or limited access.
* **File Persistence:** All clients and users are stored in text files for long-term storage.

**Purpose:**
This project simulates a real banking environment where multiple users can manage client accounts securely, respecting their roles and permissions.

**Technologies used:**

* C++ standard library (`iostream`, `fstream`, `vector`, `string`, `iomanip`)
* File handling for persistent data storage
* Modular design with **functions for each feature**
* Permission-based access control

---

## **2️⃣ Key Screens and Example Outputs**

### **2a. Login Screen**

```
------------------------------------
        Login Screen
------------------------------------
Enter User Name ? Admin
Enter Password ? 12345

Login successful!
```

**Explanation:**

* This is the first interaction with the system.
* Validates users against stored credentials in `Users.txt`.
* Supports retry until valid login.
* Motivational note: This shows **secure access and user validation**.

---

### **2b. Main Menu Screen**

```
================================================
        Main Menu Screen
================================================
[1] Show Client List.
[2] Add New Client.
[3] Delete Client.
[4] Update Client Info.
[5] Find Client.
[6] Transactions.
[7] Manage Users.
[8] Logout.
[9] Exit.
================================================
Choose what do you want to do? [1 to 9]? 
```

**Explanation:**

* This is the **central hub** of the system.
* Options available depend on the **user permissions**.
* Motivational note: It demonstrates **user-driven navigation and modular design**.

---

### **2c. Show All Clients Screen**

```
                        Client List (3) Client(s)
__________________________________________________________________________________________________

| Account Number | Pin Code  | Client Name             | Phone          | Balance   
__________________________________________________________________________________________________

| 10001          | 1234      | Ali Knj                | 555-0101       | 5000
| 10002          | 5678      | Sara Ali               | 555-0202       | 3200
| 10003          | 9876      | John Doe               | 555-0303       | 4500
__________________________________________________________________________________________________
```

**Explanation:**

* Displays all clients in a **tabular format**.
* Good use of **formatted printing** (`setw`) for readability.
* Motivational note: Users can **quickly visualize client data**.

---

### **2d. Delete Client Screen**

```
-----------------------------------
        Delete Client Screen
___________________________________

Please enter Account Number ? 10002

The following is the extracted client record:
Account Number : 10002
Pin Code       : 5678
Name           : Sara Ali
Phone          : 555-0202
Account Balance: 3200

Are you sure you want delete this client ?(y/n) ? y

Client Deleted Successfully
```

**Explanation:**

* Shows **confirmation before deletion** for safety.
* Marks client as deleted in memory and persists changes to the file.
* Motivational note: This demonstrates **safe operations and user confirmation**.

---

### **2e. Transactions Screen**

```
====================================================
        Transactions Menu Screen
====================================================
[1] Deposit.
[2] Withdraw.
[3] Total Balance.
[4] Main Menu.
====================================================
Choose what do you want to do? [1 to 4]? 1
```

**Example: Deposit Operation**

```
Please enter Account Number ? 10001

The following is the extracted client record:
Account Number : 10001
Pin Code       : 1234
Name           : Ali Knj
Phone          : 555-0101
Account Balance: 5000

Please enter deposit amount ? 2000
Are you sure you want to perform this transaction? (y/n) ? y

Done successfully, New Balance = 7000
```

**Explanation:**

* Supports **deposit, withdrawal, and balance checking**.
* Ensures **transaction safety** by asking for confirmation.
* Motivational note: **Financial operations are secure and tracked**.

---

### **2f. Update User Screen**

```
-----------------------------------------
         Update User Screen
-----------------------------------------

Please enter User Name ? Manager

The following are the user details :
User Name   : Manager
Password    : 98765
Permessions : 63

Are you sure you want to Update this User ? y/n? y

Enter Password ? 67890
Do you want to give full access? y/n? n
...
User Updated Successfully.
```

**Explanation:**

* Supports **role and permission updates**.
* Encourages **structured user management**.
* Motivational note: The system allows **role-based security**, a real-world banking practice.

---

## **3️⃣ Permission Structure**

**Permissions in this system are bitwise-coded:**

| Permission       | Value |
| ---------------- | ----- |
| Full Access      | -1    |
| Show Client List | 1     |
| Add New Client   | 2     |
| Delete Client    | 4     |
| Update Client    | 8     |
| Find Client      | 16    |
| Transactions     | 32    |
| Manage Users     | 64    |

**How it works:**

* Each user has a **Permission integer**.
* Access checks are performed using **bitwise operations**:

```cpp
if ((CurrentUser.Permission & enShowClientListP) == enShowClientListP) { ... }
```

* Full access (`-1`) overrides all checks.
* Motivational note: This allows **fine-grained access control** with minimal code complexity.

---

## **4️⃣ Code Structure & Design Highlights**

* **Modular Functions:** Each screen and operation has its own function (`ShowAddNewClientsScreen`, `DepositBalanceToClientByAccountNumber`).
* **Separation of Concerns:**

  * File operations separated from logic
  * User interface separated from data processing
* **Reusability:** Functions like `FindClientByAccountNumber` and `ConvertClientLineToRecord` are **reusable across the system**.
* **Readable & Clear Naming:** Functions and variables are self-descriptive.
* **Functional Programming Elements:** Minimal side effects in most operations.
* **Easy Maintenance:** Adding new screens, permissions, or operations is straightforward.
* **Data Safety:** Deletion is **soft (MarkForDelete)**, with confirmation prompts.
* **Consistency:** Use of `setw` and formatting for clean tables.

---

## **5️⃣ Additional Project Strengths**

* Encourages **thinking in real-world banking terms**.
* Demonstrates **file persistence and CRUD operations**.
* Uses **bitwise operations** for permission management—a **good practice in scalable systems**.
* Each **menu loops back to main menu**, ensuring smooth navigation.
* Handles **invalid input and access denial gracefully**.
* Logical flow: login → main menu → client/user/transaction operations → confirmations → persist changes.

---

## ✅ **Summary**

**This Bank Management System provides:**

* Secure login with permission control.
* CRUD operations for clients and users.
* Financial transaction handling (deposit/withdraw/check balance).
* Modular, maintainable, and reusable code design.
* Clear separation of logic and interface.
* Motivational and educational example of real-world software engineering principles.

---
