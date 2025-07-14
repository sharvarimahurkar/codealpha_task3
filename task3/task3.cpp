#include <iostream>
#include <vector>
#include <ctime>
using namespace std;

// ================= Transaction Class =================
class Transaction {
public:
    string type;
    double amount;
    string timestamp;

    Transaction(string type, double amount) {
        this->type = type;
        this->amount = amount;
        time_t now = time(0);
        timestamp = ctime(&now);
        timestamp.pop_back(); // remove newline
    }

    void showTransaction() {
        cout << timestamp << " | " << type << " | ₹" << amount << endl;
    }
};

// ================= Account Class =================
class Account {
private:
    int accountNumber;
    double balance;
    vector<Transaction> history;

public:
    Account(int accNo) {
        accountNumber = accNo;
        balance = 0.0;
    }

    int getAccountNumber() {
        return accountNumber;
    }

    double getBalance() {
        return balance;
    }

    void deposit(double amount) {
        balance += amount;
        history.push_back(Transaction("Deposit", amount));
        cout << "Amount ₹" << amount << " deposited successfully.\n";
    }

    bool withdraw(double amount) {
        if (amount > balance) {
            cout << "Insufficient balance!\n";
            return false;
        }
        balance -= amount;
        history.push_back(Transaction("Withdraw", amount));
        cout << "Amount ₹" << amount << " withdrawn successfully.\n";
        return true;
    }

    bool transferTo(Account &to, double amount) {
        if (withdraw(amount)) {
            to.deposit(amount);
            history.push_back(Transaction("Transferred to " + to_string(to.getAccountNumber()), amount));
            return true;
        }
        return false;
    }

    void showHistory() {
        cout << "\nTransaction History for Account #" << accountNumber << ":\n";
        for (auto &t : history)
            t.showTransaction();
    }

    void showDetails() {
        cout << "Account Number: " << accountNumber << "\n";
        cout << "Current Balance: ₹" << balance << "\n";
        showHistory();
    }
};

// ================= Customer Class =================
class Customer {
private:
    string name;
    int customerId;
    Account account;

public:
    Customer(int id, string name, int accNo)
        : customerId(id), name(name), account(accNo) {}

    int getCustomerId() {
        return customerId;
    }

    Account &getAccount() {
        return account;
    }

    void showCustomerInfo() {
        cout << "Customer ID: " << customerId << ", Name: " << name << "\n";
        account.showDetails();
    }
};

// ================= Menu Functions =================
void showMenu() {
    cout << "\n=== BANKING SYSTEM MENU ===\n";
    cout << "1. Deposit\n";
    cout << "2. Withdraw\n";
    cout << "3. Transfer Funds\n";
    cout << "4. View Balance & Transactions\n";
    cout << "5. Exit\n";
    cout << "Enter your choice: ";
}

// ================= Main Function =================
int main() {
    Customer cust1(1, "Sharvari", 1001);
    Customer cust2(2, "Riya", 1002);

    int choice;
    double amount;

    do {
        showMenu();
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter amount to deposit: ₹";
            cin >> amount;
            cust1.getAccount().deposit(amount);
            break;

        case 2:
            cout << "Enter amount to withdraw: ₹";
            cin >> amount;
            cust1.getAccount().withdraw(amount);
            break;

        case 3:
            cout << "Enter amount to transfer to Riya: ₹";
            cin >> amount;
            cust1.getAccount().transferTo(cust2.getAccount(), amount);
            break;

        case 4:
            cust1.showCustomerInfo();
            break;

        case 5:
            cout << "Exiting system. Thank you!\n";
            break;

        default:
            cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 5);

    return 0;
}