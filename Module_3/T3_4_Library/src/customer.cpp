#include "customer.hpp"

// Constructor
Customer::Customer(const std::string& name, const std::string& id)
    : name_(name), id_(id) {
}

// Getters
std::string Customer::GetName() const { return name_; }
std::string Customer::GetID() const { return id_; }
int Customer::GetLoanAmount() const { return loans_.size(); }

// Print customer details and their loans
void Customer::Print() const {
    std::cout << "Customer: " << name_ << ", " << id_ 
              << ", has " << loans_.size() << " books on loan:" << std::endl;
    for (const auto& book : loans_) {
        std::cout << "- ";
        book.Print();
    }
}

// Loan a book: Checks availability, updates book status, adds to vector
void Customer::LoanBook(Book& b) {
    if (b.Loan()) {
        loans_.push_back(b);
    }
}

// Return a book: Updates book status, removes from vector
void Customer::ReturnBook(Book& b) {
    // Iterate through loans to find the matching book (by ISBN)
    for (auto it = loans_.begin(); it != loans_.end(); ++it) {
        if (it->GetISBN() == b.GetISBN()) {
            b.Restore();        // Reset status on the original object
            loans_.erase(it);   // Remove from customer's list
            return;             // Stop after finding the book
        }
    }
}