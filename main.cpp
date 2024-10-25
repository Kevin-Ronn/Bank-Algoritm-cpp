
#include <iostream>
#include <vector>
#include <map>
#include <iomanip>  // För std::setw och std::setfill
#include <chrono>

class BankAccount {
    std::string accountNumber;
    float balance;
public:
    BankAccount() : balance(0) {}

    BankAccount(std::string accountNumber, float balance = 0)
        : accountNumber(accountNumber), balance(balance) {}

    std::string getAccountNumber() const {
        return accountNumber;
    }
};

// Gränssnitt för kontolagring
class IAccountStorage {
public:    
    virtual void addAccount(BankAccount account) = 0;
    virtual BankAccount* findAccount(std::string accountNumber) = 0;
};

class Bank {
private:
    IAccountStorage* accountStorage;
public:
    Bank(IAccountStorage* storage) : accountStorage(storage) {}

    bool addAccount(std::string accountNumber) {
        BankAccount account(accountNumber);
        accountStorage->addAccount(account);
        return true;
    }

    BankAccount* getAccount(std::string accountNumber) {
        return accountStorage->findAccount(accountNumber);
    }
};

// Implementeringar av olika lagringsstrategier (MapAccountStorage, VectorAccountStorage, DistributedVectorAccountStorage - samma som tidigare) 

int main(int, char**) {
    DistributedVectorAccountStorage storage;
    Bank bank(&storage);

    const int AntalAccounts = 1000000;

    std::string sFirst = ""; 
    std::string sLast = ""; 
    std::string sNotFound = "notfound"; 

    std::cout << "INITIALIZE: " << std::endl;
    auto startTime = std::chrono::high_resolution_clock::now();
    for(int i = 0; i < AntalAccounts; i++) {
        // Skapa paddat kontonummer med 10 tecken, utfyllt med nollor
        std::ostringstream oss;
        oss << std::setw(10) << std::setfill('0') << i;
        std::string accountNumber = oss.str();

        if(i == 0) {
            sFirst = accountNumber;
        }
        if(i == AntalAccounts - 1) {
            sLast = accountNumber;
        }
        bank.addAccount(accountNumber);
    }
    auto endTime = std::chrono::high_resolution_clock::now();
    std::cout << "INIT Took: " << std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count() << " milliseconds" << std::endl;

    // Testa att hämta första kontot
    startTime = std::chrono::high_resolution_clock::now();
    BankAccount* p = bank.getAccount(sFirst);
    endTime = std::chrono::high_resolution_clock::now();
    if (p != nullptr) {
        std::cout << p->getAccountNumber() << " took: " << std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count() << " milliseconds" << std::endl;
    } else {
        std::cout << "Account not found (first)" << std::endl;
    }

    // Testa att hämta sista kontot
    startTime = std::chrono::high_resolution_clock::now();
    p = bank.getAccount(sLast);
    endTime = std::chrono::high_resolution_clock::now();
    if (p != nullptr) {
        std::cout << p->getAccountNumber() << " took: " << std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count() << " milliseconds" << std::endl;
    } else {
        std::cout << "Account not found (last)" << std::endl;
    }

    // Testa att hämta ett konto som inte finns
    startTime = std::chrono::high_resolution_clock::now();
    p = bank.getAccount(sNotFound);
    endTime = std::chrono::high_resolution_clock::now();
    if (p == nullptr) {
        std::cout << "NOT FOUND took: " << std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count() << " milliseconds" << std::endl;
    }
}
