#include "library.hpp"

Library::Library(const std::string& name) : name_(name) {}

std::string Library::GetName() const { return name_; }

std::vector<Book>& Library::GetBooks() {
    return books_;
}

std::vector<Customer>& Library::GetCustomers() {
    return customers_;
}

Book Library::FindBookByName(const std::string& name) {
    for (const auto& book : books_) {
        if (book.GetName() == name) {
            return book;
        }
    }
    // Return a dummy book if not found
    return Book("", "", "");
}

std::vector<Book> Library::FindBooksByAuthor(const std::string& author) {
    std::vector<Book> result;
    for (const auto& book : books_) {
        if (book.GetAuthor() == author) {
            result.push_back(book);
        }
    }
    return result;
}

std::vector<Book> Library::FindAllLoanedBooks() {
    std::vector<Book> result;
    for (const auto& book : books_) {
        if (book.GetStatus()) {
            result.push_back(book);
        }
    }
    return result;
}

Customer Library::FindCustomer(const std::string& id) {
    for (const auto& cust : customers_) {
        if (cust.GetID() == id) {
            return cust;
        }
    }
    // Return a dummy customer if not found
    return Customer("", "");
}