#include "customer.hpp"
#include <iostream>

Customer::Customer(const std::string& name, const std::string& id)
    : name_(name), id_(id) {}

std::string Customer::GetName() const { return name_; }

std::string Customer::GetID() const { return id_; }

int Customer::GetLoanAmount() const { return loans_.size(); }

std::vector<Book> Customer::GetLoans() const { return loans_; }

bool Customer::LoanBook(Book& b) {
  if (b.Loan()) {
    loans_.push_back(b);
    return true;
  }
  return false;
}

void Customer::ReturnBook(Book& b) {
  // First, restore the status of the actual book object passed in
  b.Restore();

  // Second, remove the corresponding book from the customer's loan list
  // We identify the book by ISBN
  for (auto it = loans_.begin(); it != loans_.end(); ++it) {
    if (it->GetISBN() == b.GetISBN()) {
      loans_.erase(it);
      break; 
    }
  }
}

void Customer::Print() const {
  std::cout << "Customer: " << name_ << ", " << id_ << ", has "
            << loans_.size() << " books on loan:" << std::endl;
  
  for (const auto& book : loans_) {
    std::cout << "- ";
    book.Print();
  }
}