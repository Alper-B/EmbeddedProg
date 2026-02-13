#ifndef CUSTOMER_HPP
#define CUSTOMER_HPP

#include <string>
#include <vector>
#include "book.hpp"

class Customer {
public:
    Customer(const std::string& name, const std::string& id);

    std::string GetName() const;
    std::string GetID() const;
    int GetLoanAmount() const;

    void Print() const;
    void LoanBook(Book& b);
    void ReturnBook(Book& b);

private:
    std::string name_;
    std::string id_;
    std::vector<Book> loans_;
};

#endif