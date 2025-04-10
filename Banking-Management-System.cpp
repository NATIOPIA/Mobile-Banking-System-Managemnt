#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

const string FILE_NAME = "mobileBanking.xlsx";

struct Account {
    int phNum;
    string Fname;
    int accNum;
    double balance; 
};

void showmenu() {
    cout << "\n--- Mobile Banking System ---\n";
    cout << "1. Create new account \n";
    cout << "2. Display accounts\n";
    cout << "3. Deposit into account\n";
    cout << "4. Withdraw from account\n";
    cout << "5. Search Account\n";
    cout << "6. Delete Account\n";
    cout << "7. Exit\n";
    cout << "Enter your choice: ";
}

bool isValidPhoneNumber(int phNum) {
    // Check if the phone number is a 10-digit number
    return (phNum >=  900000000&& phNum <= 1000000000);
}
    //Checking account number validity
bool isValidAccountNumber(int accNum) {
    // Check if the account number is between 1000000000000 and 00000000000
    return (accNum <= 100000000000 && accNum >= 0000000000000);
}

void newAccount() {
    Account newAccount;
    newAccount.balance = 0.0; 
    ofstream addAccount(FILE_NAME, ios::app); 

    cout << "Enter full name: ";
    cin.ignore();
    getline(cin, newAccount.Fname);

    do {
        cout << "Enter phone number (10 digits start with 09--): ";
        cin >> newAccount.phNum;
        if (!isValidPhoneNumber(newAccount.phNum)) {
            cout << "Invalid phone number. Please enter a 10-digit numberor start with 09--." << endl;
        }
    } while (!isValidPhoneNumber(newAccount.phNum));

    do {
        cout << "Enter new account number (between 0000000000000 and 100000000000): ";
        cin >> newAccount.accNum;
        if (!isValidAccountNumber(newAccount.accNum)) {
            cout << "Invalid account number. Please enter a number between 0000000000000 and 100000000000." << endl;
        }
    } while (!isValidAccountNumber(newAccount.accNum));

    addAccount << newAccount.Fname << " , " << newAccount.phNum << " , " << newAccount.accNum << " , " << newAccount.balance << endl;
    addAccount.close();

    cout << "\n--- Account created successfully! ---\n" << endl;
}

void displayAccounts() {
    ifstream readAccounts(FILE_NAME);
    if (!readAccounts) {
        cout << "Error opening file!" << endl;
        return;
    }

    cout << "\n--- List of Accounts ---\n";
    string line;
    while (getline(readAccounts, line)) {
        cout << line << endl;
    }
    readAccounts.close();
}

void depositIntoAccount() {
    int accNum;
    double depositAmount;
    bool accountFound = false;
    Account tempAccount;
    ifstream readAccounts(FILE_NAME);
    ofstream tempFile("temp.xlsx"); 

    cout << "Enter account number to deposit into: ";
    cin >> accNum;

    while (readAccounts >> ws && getline(readAccounts, tempAccount.Fname, ',') &&
           readAccounts >> tempAccount.phNum >> ws && 
           readAccounts.ignore(1) && // Ignore the comma
           readAccounts >> tempAccount.accNum >> ws && 
           readAccounts.ignore(1) && // Ignore the comma
           readAccounts >> tempAccount.balance) {
        
        if (tempAccount.accNum == accNum) {
            accountFound = true;
            cout << "Current balance: " << tempAccount.balance << endl;
            cout << "Enter amount to deposit: ";
            cin >> depositAmount;
            tempAccount.balance += depositAmount; // Update balance
            cout << "New balance: " << tempAccount.balance << endl;
        }
        tempFile << tempAccount.Fname << " , " << tempAccount.phNum << " , " << tempAccount.accNum << " , " << tempAccount.balance << endl;
    }

    readAccounts.close();
    tempFile.close();

    remove(FILE_NAME.c_str());
    rename("temp.xlsx", FILE_NAME.c_str());

    if (accountFound) {
        cout << "\n--- Deposit successful! ---\n" << endl;
    } else {
        cout << "Account number not found." << endl;
    }
}

void withdrawFromAccount() {
    int accNum;
    double withdrawAmount;
    bool accountFound = false;
    Account tempAccount;
    ifstream readAccounts(FILE_NAME);
    ofstream tempFile("temp.xlsx"); 

    cout << "Enter account number to withdraw from: ";
    cin >> accNum;

    while (readAccounts >> ws && getline(readAccounts, tempAccount.Fname, ',') &&
           readAccounts >> tempAccount.phNum >> ws && 
           readAccounts.ignore(1) && // Ignore the comma
           readAccounts >> tempAccount.accNum >> ws && 
           readAccounts.ignore(1) && // Ignore the comma
           readAccounts >> tempAccount.balance) {
        
        if (tempAccount.accNum == accNum) {
            accountFound = true;
            cout << "Current balance: " << tempAccount.balance << endl;
            cout << "Enter amount to withdraw: ";
            cin >> withdrawAmount;

            // Validate withdraw amount
            if (withdrawAmount <= 0) {
                cout << "Invalid withdraw amount. Please enter a positive value." << endl;
                return;
            }

            if (withdrawAmount > tempAccount.balance) {
                cout << "Insufficient balance!" << endl;
                return;
            }

            tempAccount.balance -= withdrawAmount; // Update balance
            cout << "New balance: " << tempAccount.balance << endl;
        }
        tempFile << tempAccount.Fname << " , " << tempAccount.phNum << " , " << tempAccount.accNum << " , " << tempAccount.balance << endl;
    }

    readAccounts.close();
    tempFile.close();

    remove(FILE_NAME.c_str());
    rename("temp.xlsx", FILE_NAME.c_str());

    if (accountFound) {
        cout << "\n--- Withdrawal successful! ---\n" << endl;
    } else {
        cout << "Account number not found." << endl;
    }
}

void searchAccount() {
    int accNum;
    bool accountFound = false;
    Account tempAccount;
    ifstream readAccounts(FILE_NAME);

    cout << "Enter account number to search: ";
    cin >> accNum;

    while (readAccounts >> ws && getline(readAccounts, tempAccount.Fname, ',') &&
           readAccounts >> tempAccount.phNum >> ws && 
           readAccounts.ignore(1) && // Ignore the comma
           readAccounts >> tempAccount.accNum >> ws && 
           readAccounts.ignore(1) && // Ignore the comma
           readAccounts >> tempAccount.balance) {
        
        if (tempAccount.accNum == accNum) {
            accountFound = true;
            cout << "\n--- Account Found ---\n";
            cout << "Full Name: " << tempAccount.Fname << endl;
            cout << "Phone Number: " << tempAccount.phNum << endl;
            cout << "Account Number: " << tempAccount.accNum << endl;
            cout << "Balance: " << tempAccount.balance << endl;
            break;
        }
    }

    readAccounts.close();

    if (!accountFound) {
        cout << "Account number not found." << endl;
    }
}

int main() {
    int choice;
    do {
        showmenu();
        cin >> choice;

        switch (choice) {
            case 1:
                newAccount();
                break;
            case 2:
                displayAccounts();
                break;
            case 3:
                depositIntoAccount(); 
                break;
            case 4:
                withdrawFromAccount();
                break;
            case 5:
                searchAccount();
                break;
            case 6:
                // Code to delete Account would go here
                break;
            case 7:
                cout << "Exiting the program." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 7);

    return 0;
}


