#ifndef LIBRARY_HPP
#define LIBRARY_HPP

#include <string>
#include <vector>
#include "book.hpp"
#include "customer.hpp"

class Library {
public:
    // Constructor
    Library(const std::string& name);

    // Getters
    std::string GetName() const;
    
    // NOTE: These return references so main can modify the vectors directly
    std::vector<Book>& GetBooks();
    std::vector<Customer>& GetCustomers();

    // Search Functions
    Book FindBookByName(const std::string& name);
    std::vector<Book> FindBooksByAuthor(const std::string& author);
    std::vector<Book> FindAllLoanedBooks();
    Customer FindCustomer(const std::string& id);

private:
    std::string name_;
    std::vector<Book> books_;
    std::vector<Customer> customers_;
};

#endif