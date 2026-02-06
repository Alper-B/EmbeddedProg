#include "customer.hpp"

#include <iostream>

Customer::Customer(const std::string& name, const std::string& id)
    : name_(name), id_(id) {}

std::string Customer::GetName() const {
    return name_;
}

std::string Customer::GetID() const {
    return id_;
}

int Customer::GetLoanAmount() const {
    return loans_.size();
}

std::vector<Book> Customer::GetLoans() const {
    return loans_;
}

bool Customer::LoanBook(Book& b) {
    if (!b.Loan()) {
        return false;
    }

    loans_.push_back(b);
    return true;
}

void Customer::ReturnBook(Book& b) {
    for (auto it = loans_.begin(); it != loans_.end(); ++it) {
        if (it->GetISBN() == b.GetISBN()) {
            loans_.erase(it);
            b.Restore();
            return;
        }
    }
}

void Customer::Print() const {
    std::cout << "Customer: " << name_
              << ", " << id_
              << ", has " << loans_.size()
              << " books on loan:" << std::endl;

    for (const auto& b : loans_) {
        std::cout << "- ";
        b.Print();
    }
}
