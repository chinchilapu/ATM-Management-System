#include <iostream>
#include <vector>
#include <string>
using namespace std;
class Account {
private:
    int accountNumber;
    string holderName;
    double balance;
    string pin;
public:
    Account(int accNum, string name, string pinCode) {
        accountNumber = accNum;
        holderName = name;
        pin = pinCode;
        balance = 0.0;
    }
    int getAccountNumber() const { return accountNumber; }
    string getHolderName() const { return holderName; }
    bool verifyPIN(const string& enteredPIN) const {
        return pin == enteredPIN;
    }
    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "Deposit successful! Current balance: Rs" << balance << "\n";
        } else {
            cout << "Invalid deposit amount.\n";
        }
    }
    void withdraw(double amount) {
        if (amount <= 0) {
            cout << "Invalid withdrawal amount.\n";
        } else if (amount > balance) {
            cout << "Insufficient funds.\n";
        } else {
            balance -= amount;
            cout << "Withdrawal successful! Remaining balance: Rs" << balance << "\n";
        }
    }
    void display() const {
        cout << "Account Number: " << accountNumber << "\n";
        cout << "Account Holder: " << holderName << "\n";
        cout << "Balance: Rs" << balance << "\n";
    }
};
void showMenu() {
    cout << "\n--- ATM Management System Menu ---\n";
    cout << "1. Create New Account\n";
    cout << "2. Access Account\n";
    cout << "3. Display All Accounts\n";
    cout << "4. Exit\n";
    cout << "----------------------------------\n";
}
Account* findAccountByNumber(vector<Account>& accounts, int accNum) {
    for (auto& acc : accounts) {
        if (acc.getAccountNumber() == accNum) {
            return &acc;
        }
    }
    return nullptr;
}
void accountOperations(Account& acc) {
    string inputPIN;
    cout << "Enter PIN for account " << acc.getAccountNumber() << ": ";
    cin >> inputPIN;

    if (!acc.verifyPIN(inputPIN)) {
        cout << "Incorrect PIN.\n";
        return;
    }
    int choice;
    do {
        cout << "\nAccount Menu:\n";
        cout << "1. Check Balance\n";
        cout << "2. Deposit\n";
        cout << "3. Withdraw\n";
        cout << "4. Exit to Main Menu\n";
        cout << "Choose an option: ";
        cin >> choice;

        switch (choice) {
            case 1:
                acc.display();
                break;
            case 2: {
                double amount;
                cout << "Enter deposit amount: ";
                cin >> amount;
                acc.deposit(amount);
                break;
            }
            case 3: {
                double amount;
                cout << "Enter withdrawal amount: ";
                cin >> amount;
                acc.withdraw(amount);
                break;
            }
            case 4:
                cout << "Returning to main menu...\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 4);
}

int main() {
    vector<Account> accounts;
    int nextAccountNumber = 1001;
    int mainChoice;

    cout << "Welcome to the ATM Management System!\n";

    do {
        showMenu();
        cout << "Select an option: ";
        cin >> mainChoice;

        switch (mainChoice) {
            case 1: {
                string name, pin;
                cout << "Enter account holder's name: ";
                cin.ignore();  
                getline(cin, name);
                cout << "Set a 4-digit PIN: ";
                cin >> pin;

                accounts.push_back(Account(nextAccountNumber, name, pin));
                cout << "Account created successfully! Your account number is: " << nextAccountNumber << "\n";
                nextAccountNumber++;
                break;
            }
            case 2: {
                int accNum;
                cout << "Enter your account number: ";
                cin >> accNum;
                Account* acc = findAccountByNumber(accounts, accNum);
                if (acc != nullptr) {
                    accountOperations(*acc);
                } else {
                    cout << "Account not found.\n";
                }
                break;
            }
            case 3:
                if (accounts.empty()) {
                    cout << "No accounts to display.\n";
                } else {
                    cout << "\nList of Accounts:\n";
                    for (const auto& acc : accounts) {
                        acc.display();
                        cout << "-----------------------\n";
                    }
                }
                break;
            case 4:
                cout << "Exiting system. Goodbye!\n";
                break;
            default:
                cout << "Invalid option. Please select again.\n";
        }
    } while (mainChoice != 4);

    return 0;
}
