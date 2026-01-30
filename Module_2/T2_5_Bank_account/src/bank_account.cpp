#include "bank_account.hpp"
#include <iostream>

// Constructor
BankAccount::BankAccount(std::string const& owner,
                         std::string const& account_number,
                         double balance)
    : owner_(owner), account_number_(account_number), balance_(balance) {}

// Accessors
std::string BankAccount::GetOwner() const {
    return owner_;
}

std::string BankAccount::GetNumber() const {
    return account_number_;
}

double BankAccount::GetBalance() const {
    return balance_;
}

// Modifiers / operations
void BankAccount::Deposit(double amount) {
    balance_ += amount;
}

bool BankAccount::Withdraw(double amount) {
    if (amount > balance_) {
        return false;
    }
    balance_ -= amount;
    return true;
}

void BankAccount::Print() const {
    std::cout << "Account num: " << account_number_
              << ", owned by: " << owner_
              << ", balance: " << balance_ << " eur." << std::endl;
}


bool Transfer(BankAccount& source_account, BankAccount& target_account, double amount) {

    if (!source_account.Withdraw(amount)) {
        return false;
    }

    target_account.Deposit(amount);
    return true;
}
