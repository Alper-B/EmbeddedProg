#include "customer.hpp"

#include <iostream>

class Customer {
 public:
  Customer(const std::string& name, const std::string& id);

  std::string GetName() const;
  std::string GetID() const;
  int GetLoanAmount() const;
  std::vector<Book> GetLoans() const;

  bool LoanBook(Book& b);
  void ReturnBook(Book& b);
  void Print() const;

 private:
  std::string name_;
  std::string id_;
  std::vector<Book> loans_;
};

