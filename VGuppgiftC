#include <iostream>
#include <string>

template <typename T, size_t Capacity>
class Queue {
private:
    T data[Capacity];    // Statisk array för att lagra könsdata
    size_t front;        // Index för det första elementet i kön
    size_t back;         // Index för nästa tillgängliga position att lägga till
    size_t count;        // Håller koll på antal element i kön

public:
    Queue() : front(0), back(0), count(0) {}

    bool isEmpty() const { return count == 0; }
    bool isFull() const { return count == Capacity; }

    // Lägg till ett element i kön, returnera false om kön är full
    bool enqueue(const T& item) {
        if (isFull()) return false;  // Returnera false om kön är full
        data[back] = item;
        back = (back + 1) % Capacity;  // Cirkulär indexering för att undvika overflow
        ++count;
        return true;
    }

    // Ta bort ett element från kön, returnera false om kön är tom
    bool dequeue(T& item) {
        if (isEmpty()) return false;  // Returnera false om kön är tom
        item = data[front];
        front = (front + 1) % Capacity;  // Flytta front-indexet framåt cirkulärt
        --count;
        return true;
    }

    // Hämta det första elementet i kön utan att ta bort det
    bool peek(T& item) const {
        if (isEmpty()) return false;  // Returnera false om kön är tom
        item = data[front];
        return true;
    }
};

// Bankkonto och transaktionsstruktur
class BankAccount {
    std::string accountNumber;
    float balance;
public:
    BankAccount(std::string accountNumber, float balance = 0) 
    : accountNumber(accountNumber), balance(balance) {}

    std::string getAccountNumber() const { return accountNumber; }
    float getBalance() const { return balance; }

    void deposit(float amount) { balance += amount; }
    bool withdraw(float amount) { 
        if (balance >= amount) {
            balance -= amount;
            return true;
        }
        return false; 
    }
};

// Struktur för transaktion
struct Transaction {
    std::string accountNumber;
    float amount;
};

// Bankklass med kö för transaktioner
template <size_t QueueCapacity>
class Bank {
private:
    Queue<Transaction, QueueCapacity> transactionQueue;

public:
    bool addTransaction(const std::string& accountNumber, float amount) {
        Transaction transaction = { accountNumber, amount };
        if (!transactionQueue.enqueue(transaction)) {
            std::cerr << "Transaction queue is full. Could not add transaction for account " 
                      << accountNumber << std::endl;
            return false;
        }
        return true;
    }

    void processTransactions(BankAccount& account) {
        Transaction transaction;
        while (transactionQueue.dequeue(transaction)) {
            if (transaction.accountNumber == account.getAccountNumber()) {
                if (transaction.amount >= 0) {
                    account.deposit(transaction.amount);
                    std::cout << "Deposited " << transaction.amount << " to account " 
                              << account.getAccountNumber() << std::endl;
                } else {
                    if (account.withdraw(-transaction.amount)) {
                        std::cout << "Withdrew " << -transaction.amount << " from account " 
                                  << account.getAccountNumber() << std::endl;
                    } else {
                        std::cerr << "Insufficient funds for withdrawal from account " 
                                  << account.getAccountNumber() << std::endl;
                    }
                }
            }
        }
    }
};

int main() {
    Bank<5> bank; // Bank med en transaktionskö med kapacitet 5
    BankAccount account("0000000001", 1000); // Konto med startbalans

    // Test: lägga till transaktioner
    bank.addTransaction("0000000001", 100);   // Insättning
    bank.addTransaction("0000000001", -50);   // Uttag
    bank.addTransaction("0000000001", 200);   // Insättning
    bank.addTransaction("0000000001", -300);  // Uttag
    bank.addTransaction("0000000001", 500);   // Insättning

    // Försök att överflöda kön
    if (!bank.addTransaction("0000000001", 600)) {
        std::cout << "Queue full, additional transaction not added." << std::endl;
    }

    // Bearbeta transaktionerna
    bank.processTransactions(account);

    std::cout << "Final balance for account " << account.getAccountNumber() 
              << ": " << account.getBalance() << std::endl;

    return 0;
}
