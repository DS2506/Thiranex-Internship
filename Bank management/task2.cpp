#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

using namespace std;

class Account {
public:
    int accountNumber;
    string name;
    double balance;

    void createAccount() {
        cout << "Enter Account Number: ";
        cin >> accountNumber;

        cin.ignore();

        cout << "Enter Account Holder Name: ";
        getline(cin, name);

        cout << "Enter Initial Balance: ";
        cin >> balance;
    }

    void displayAccount() const {
        cout << left << setw(15) << accountNumber
             << setw(25) << name
             << setw(15) << fixed << setprecision(2) << balance
             << endl;
    }
};

void addAccount() {
    Account acc;

    ofstream file("bank.txt", ios::app);

    if (!file) {
        cout << "Unable to open file.\n";
        return;
    }

    acc.createAccount();

    file << acc.accountNumber << "|"
         << acc.name << "|"
         << acc.balance << endl;

    file.close();

    cout << "\nAccount created successfully.\n";
}

vector<Account> loadAccounts() {
    vector<Account> accounts;

    ifstream file("bank.txt");

    if (!file) {
        return accounts;
    }

    string line;
    Account acc;

    while (getline(file, line)) {
        size_t pos1 = line.find('|');
        size_t pos2 = line.find('|', pos1 + 1);

        acc.accountNumber = stoi(line.substr(0, pos1));
        acc.name = line.substr(pos1 + 1, pos2 - pos1 - 1);
        acc.balance = stod(line.substr(pos2 + 1));

        accounts.push_back(acc);
    }

    file.close();

    return accounts;
}

void saveAccounts(const vector<Account>& accounts) {
    ofstream file("bank.txt");

    for (const auto& acc : accounts) {
        file << acc.accountNumber << "|"
             << acc.name << "|"
             << acc.balance << endl;
    }

    file.close();
}

void displayAccounts() {
    vector<Account> accounts = loadAccounts();

    if (accounts.empty()) {
        cout << "\nNo accounts found.\n";
        return;
    }

    cout << "\n";
    cout << left << setw(15) << "Account No"
         << setw(25) << "Name"
         << setw(15) << "Balance" << endl;

    cout << string(55, '-') << endl;

    for (const auto& acc : accounts) {
        acc.displayAccount();
    }
}

void depositMoney() {
    vector<Account> accounts = loadAccounts();

    int accNo;
    double amount;
    bool found = false;

    cout << "Enter Account Number: ";
    cin >> accNo;

    cout << "Enter Deposit Amount: ";
    cin >> amount;

    for (auto& acc : accounts) {
        if (acc.accountNumber == accNo) {
            acc.balance += amount;
            found = true;

            cout << "Deposit successful.\n";
            cout << "Updated Balance: " << acc.balance << endl;

            break;
        }
    }

    if (!found) {
        cout << "Account not found.\n";
        return;
    }

    saveAccounts(accounts);
}

void withdrawMoney() {
    vector<Account> accounts = loadAccounts();

    int accNo;
    double amount;
    bool found = false;

    cout << "Enter Account Number: ";
    cin >> accNo;

    cout << "Enter Withdrawal Amount: ";
    cin >> amount;

    for (auto& acc : accounts) {
        if (acc.accountNumber == accNo) {

            if (amount > acc.balance) {
                cout << "Insufficient balance.\n";
                return;
            }

            acc.balance -= amount;
            found = true;

            cout << "Withdrawal successful.\n";
            cout << "Remaining Balance: " << acc.balance << endl;

            break;
        }
    }

    if (!found) {
        cout << "Account not found.\n";
        return;
    }

    saveAccounts(accounts);
}

void checkBalance() {
    vector<Account> accounts = loadAccounts();

    int accNo;
    bool found = false;

    cout << "Enter Account Number: ";
    cin >> accNo;

    for (const auto& acc : accounts) {
        if (acc.accountNumber == accNo) {
            cout << "\nAccount Holder: " << acc.name << endl;
            cout << "Current Balance: " << fixed << setprecision(2)
                 << acc.balance << endl;

            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Account not found.\n";
    }
}

int main() {
    int choice;

    do {
        cout << "\n========== Bank Management System ==========\n";
        cout << "1. Create Account\n";
        cout << "2. Display Accounts\n";
        cout << "3. Deposit Money\n";
        cout << "4. Withdraw Money\n";
        cout << "5. Check Balance\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";

        cin >> choice;

        switch (choice) {

            case 1:
                addAccount();
                break;

            case 2:
                displayAccounts();
                break;

            case 3:
                depositMoney();
                break;

            case 4:
                withdrawMoney();
                break;

            case 5:
                checkBalance();
                break;

            case 6:
                cout << "Exiting program.\n";
                break;

            default:
                cout << "Invalid choice.\n";
        }

    } while (choice != 6);

    return 0;
}