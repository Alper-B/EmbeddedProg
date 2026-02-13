#include "customer.hpp"
#include <iostream>

Customer::Customer(const std::string& name, const std::string& id)
    : name_(name), id_(id) {
}

std::string Customer::GetName() const { return name_; }
std::string Customer::GetID() const { return id_; }
int Customer::GetLoanAmount() const { return loans_.size(); }

void Customer::Print() const {
    std::cout << "Customer: " << name_ << ", " << id_ 
              << ", has " << loans_.size() << " books on loan:" << std::endl;
    for (const auto& book : loans_) {
        std::cout << "- ";
        book.Print();
    }
}

void Customer::LoanBook(Book& b) {
    if (b.Loan()) {
        loans_.push_back(b);
    }
}

void Customer::ReturnBook(Book& b) {
    // We must find the book in the loans vector by ISBN
    for (auto it = loans_.begin(); it != loans_.end(); ++it) {
        if (it->GetISBN() == b.GetISBN()) {
            b.Restore();        // Reset status on the physical book object
            loans_.erase(it);   // Remove the record from customer
            return;
        }
    }
}