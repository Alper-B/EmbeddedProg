#ifndef LIBRARY_HPP
#define LIBRARY_HPP

#include <string>
#include <vector>
#include "book.hpp"
#include "customer.hpp"

class Library {
public:
    Library(const std::string& name);

    std::string GetName() const;
    
    // Must return references so main can modify the library's contents
    std::vector<Book>& GetBooks();
    std::vector<Customer>& GetCustomers();

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