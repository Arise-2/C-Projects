#include <iostream>
#include <fstream>
using namespace std;

const int MAX_TRANSACTIONS = 100;
const int MAX_WALLETS = 10;

class Transaction{
   public:
    string date, type, description;
    double amount;

    Transaction() {}

    Transaction(string d,string t,double amt,string desc) {
        date=d;
        type=t;
        amount=amt;
        description=desc;
    }


    void display() {
        cout<<"\nDate: "<<date<<"\nType: "<< type<<"\nAmount: Rs. "<< amount<< "\nDescription: "<<description<<"\n-------------------";
    }

    ~Transaction() {}
};


class User{
    public:
        string ownerName; 
        User() {}
        User(string name) {
        ownerName = name;
        }
    };
    

class Wallet:public User{
public:
    string walletId;
    double balance;
    Transaction transactions[MAX_TRANSACTIONS];
    int transactionCount;

     static int totalWallets;

    Wallet() {}

    Wallet(string id, string name){
        ownerName = name;      
        walletId = id;
        balance = 0;
        transactionCount = 0;
        totalWallets++;
    }
    
    void addMoney(double amount){
        addMoney(amount, "Added money");
    }

    void addMoney(double amount, string description){
        if (amount > 0){
            balance += amount;
            transactions[transactionCount++]=Transaction("2024-03-20","CREDIT",amount,description);
            cout<<"\nRs. "<<amount<<" added successfully!";
        } else{
            cout<<"\nInvalid amount!";
        }
    }

    void withdrawMoney(double amount){
        if (amount > 0 && amount <= balance){
            balance -= amount;
            transactions[transactionCount++]=Transaction("2024-03-20","DEBIT",amount,"Withdrawn money");
            cout << "\nRs. " << amount << " withdrawn successfully!";
        } else {
            cout<<"\nInsufficient balance!";
        }
    }

    void viewTransactions() {
        if (transactionCount==0) {
            cout<<"\nNo transactions yet.";
        } else {
            cout<<"\nTransaction History:";
            for (int i =0; i<transactionCount; i++) {
                transactions[i].display();
            }
        }
    }

    friend void viewBalance(const Wallet &w); 

    
    void saveToFile() {
        ofstream file(walletId +".txt");
        file<<"Wallet ID: "<<walletId<<"\nOwner: "<<ownerName<<"\nBalance: "<< balance << "\n";
        for (int i = 0; i < transactionCount; i++) {
            file<<transactions[i].date<<","<<transactions[i].type<<","<<transactions[i].amount<<","<<transactions[i].description<<"\n";
        }
        file.close();
    }

    void readFromFile() {
        ifstream file(walletId +".txt");
        string line;
        cout << "\nReading Wallet Data from File:\n";
        while (getline(file, line)) {
            cout << line << endl;
        }
        file.close();
    }

    ~Wallet() {}
        
};


int Wallet::totalWallets = 0;


void viewBalance(const Wallet &w) {
    cout<<"\nBalance: Rs. "<< w.balance;
}

int main() {
    Wallet wallets[MAX_WALLETS];
    int walletCount =0;
    int choice;
    string id, name;
    double amount;

    while(true) {
        cout<< "\n\n=== Digital Wallet System ==="<< "\n1. Create Wallet"<< "\n2. Add Money"<< "\n3. Withdraw Money"<< "\n4. View Balance"<< "\n5. View Transactions"
             << "\n6. Save Wallet to File"<< "\n7. Read Wallet from File"<< "\n8. Show Total Wallets"<< "\n9. Exit"<< "\nEnter choice: ";
        cin>>choice;

        if (choice==9) {
            cout << "\nThank you for using the Digital Wallet System!\n";
            break;
        }

        if (choice == 1) {
            if (walletCount < MAX_WALLETS) {
                cout << "Enter Wallet ID: ";
                cin >> id;
                cout << "Enter Owner Name: ";
                cin.ignore();
                getline(cin, name);
                wallets[walletCount++] = Wallet(id, name);
                cout<<"\nWallet created!";
            } else {
                cout<<"\nMaximum wallets reached!";
            }
        } else {
            cout<<"\nEnter Wallet ID: ";
            cin>>id;

            Wallet *wallet=nullptr;
            for(int i = 0; i < walletCount; i++) {
                if (wallets[i].walletId == id) {
                    wallet=&wallets[i];
                    break;
                }
            }

            if (wallet != nullptr) {
                switch (choice) {
                    case 2:
                        cout << "Enter amount to add: ";
                        cin >> amount;
                        wallet->addMoney(amount);
                        break;
                    case 3:
                        cout << "Enter amount to withdraw: ";
                        cin >> amount;
                        wallet->withdrawMoney(amount);
                        break;
                    case 4:
                        viewBalance(*wallet);
                        break;
                    case 5:
                        wallet->viewTransactions();
                        break;
                    case 6:
                        wallet->saveToFile();
                        cout << "\nWallet data saved to file!";
                        break;
                    case 7:
                        wallet->readFromFile();
                        break;
                    case 8:
                        cout << "\nTotal Wallets Created: " << Wallet::totalWallets;
                        break;
                    default:
                        cout << "\nInvalid choice!";
                }
            } else {
                cout << "\nWallet not found!";
            }
        }
    }
}
