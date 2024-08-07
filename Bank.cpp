#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

class BankAccount {
private:
    string name;
    int accountNum;
    double balance;

public:
    BankAccount(string n = "", int ac = 0, double bal = 0.0) : name(n), accountNum(ac), balance(bal) {}

    string getName() const {
        return name;
    }

    int getAccountNum() const {
        return accountNum;
    }

    double getBalance() const {
        return balance;
    }

    void deposit(double amount) {
        balance += amount;
    }

    void withdraw(double amount) {
        if (balance >= amount) {
            balance -= amount;
            cout << "\t\tWithdraw Successfully..." << endl;
        } else {
            cout << "\t\tInsufficient Balance...." << endl;
        }
    }

    void saveToFile(ofstream &out) const {
        out << name << endl;
        out << accountNum << endl;
        out << balance << endl;
    }

    void loadFromFile(ifstream &in) {
        getline(in, name);
        in >> accountNum;
        in >> balance;
        in.ignore(); // To ignore the newline character after the balance
    }
};

class BankManagement {
private:
    vector<BankAccount> accounts;

public:
    void AddAccount(const string &name, int accountNum, double balance) {
        accounts.push_back(BankAccount(name, accountNum, balance));
    }

    void showAllAccounts() const {
        cout << "\t\tAll Account Holders " << endl;
        for (size_t i = 0; i < accounts.size(); ++i) {
            const BankAccount& account = accounts[i];
            cout << "Name :" << account.getName() << " Account Number :" << account.getAccountNum() << " Balance :" << account.getBalance() << endl;
        }
    }

    void searchAccount(int account) const {
        cout << "\t\tAccount Holder " << endl;
        for (size_t i = 0; i < accounts.size(); ++i) {
            const BankAccount& accountItem = accounts[i];
            if (accountItem.getAccountNum() == account) {
                cout << "Name :" << accountItem.getName() << " Account Number :" << accountItem.getAccountNum() << " Balance :" << accountItem.getBalance() << endl;
                return;
            }
        }
        cout << "\t\tAccount Not Found..." << endl;
    }

    BankAccount* findAccount(int accountNum) {
        for (size_t i = 0; i < accounts.size(); ++i) {
            if (accounts[i].getAccountNum() == accountNum) {
                return &accounts[i];
            }
        }
        return NULL;
    }

    void saveToFile(const string &filename) const {
        ofstream out(filename.c_str());
        if (out.is_open()) {
            for (size_t i = 0; i < accounts.size(); ++i) {
                accounts[i].saveToFile(out);
            }
            out.close();
        } else {
            cout << "Error opening file for writing." << endl;
        }
    }

    void loadFromFile(const string &filename) {
        ifstream in(filename.c_str());
        if (in.is_open()) {
            accounts.clear(); // Clear existing accounts
            while (!in.eof()) {
                BankAccount account;
                account.loadFromFile(in);
                if (in) { // Check for successful read
                    accounts.push_back(account);
                }
            }
            in.close();
        } else {
            cout << "Error opening file for reading." << endl;
        }
    }
};

int main() {
    BankManagement bank;
    bank.loadFromFile("accounts.txt"); // Load existing accounts from file

    int choice;
    char op;

    do {
        system("cls");
        cout << "\t\t::Bank Management System" << endl;
        cout << "\t\t\tMain Menu" << endl;
        cout << "\t\t1. Create New Account" << endl;
        cout << "\t\t2. Show All Account" << endl;
        cout << "\t\t3. Search Account" << endl;
        cout << "\t\t4. Deposit Money" << endl;
        cout << "\t\t5. Withdraw Money" << endl;
        cout << "\t\t6. Exit" << endl;
        cout << "\t\t-------------------------------" << endl;
        cout << "\t\tEnter Your Choice :";
        cin >> choice;

        switch (choice) {
            case 1: {
                string name;
                int accountNum;
                double balance;
                cout << "\t\tEnter Name :";
                cin >> name;
                cout << "\t\tEnter Account Number :";
                cin >> accountNum;
                cout << "\t\tEnter Initial Balance :";
                cin >> balance;
                bank.AddAccount(name, accountNum, balance);
                cout << "\t\tAccount Created Successfully...." << endl;
                break;
            }
            case 2: {
                bank.showAllAccounts();
                break;
            }
            case 3: {
                int accountNum;
                cout << "Enter Account Number :";
                cin >> accountNum;
                bank.searchAccount(accountNum);
                break;
            }
            case 4: {
                int accountNum;
                double amount;
                cout << "\t\tEnter Account Number to Deposit Money :";
                cin >> accountNum;
                BankAccount* account = bank.findAccount(accountNum);
                if (account != NULL) {
                    cout << "\t\tEnter Amount to Deposit :";
                    cin >> amount;
                    account->deposit(amount);
                    cout << "\t\t" << amount << " Deposit Successfully ...." << endl;
                } else {
                    cout << "\t\tAccount Not Found ..." << endl;
                }
                break;
            }
            case 5: {
                int accountNum;
                double amount;
                cout << "\t\tEnter Account Number to Withdraw Money :";
                cin >> accountNum;
                BankAccount* account = bank.findAccount(accountNum);
                if (account != NULL) {
                    cout << "\t\tEnter Amount to withdraw :";
                    cin >> amount;
                    account->withdraw(amount);
                } else {
                    cout << "\t\tAccount Not Found ..." << endl;
                }
                break;
            }
            case 6: {
                bank.saveToFile("accounts.txt"); // Save accounts to file
                exit(0);
            }
        }
        cout << "\t\tDo You Want to Continue or Exit [Yes/No] ??";
        cin >> op;

    } while (op == 'y' || op == 'Y');

    return 0;
}

