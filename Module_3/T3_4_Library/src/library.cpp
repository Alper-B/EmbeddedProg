#include "library.hpp"

// Constructor
Library::Library(const std::string& name) : name_(name) {}

// Getters
std::string Library::GetName() const { return name_; }

std::vector<Book>& Library::GetBooks() { 
    return books_; 
}

std::vector<Customer>& Library::GetCustomers() { 
    return customers_; 
}

// Find a single book by exact name match
Book Library::FindBookByName(const std::string& name) {
    for (const auto& book : books_) {
        if (book.GetName() == name) {
            return book;
        }
    }
    // Return a dummy book if not found (implied by exercise structure)
    return Book("", "", "");
}

// Find all books by a specific author
std::vector<Book> Library::FindBooksByAuthor(const std::string& author) {
    std::vector<Book> found_books;
    for (const auto& book : books_) {
        if (book.GetAuthor() == author) {
            found_books.push_back(book);
        }
    }
    return found_books;
}

// Find all books currently marked as loaned
std::vector<Book> Library::FindAllLoanedBooks() {
    std::vector<Book> loaned_books;
    for (const auto& book : books_) {
        if (book.GetStatus()) {
            loaned_books.push_back(book);
        }
    }
    return loaned_books;
}

// Find a customer by ID
Customer Library::FindCustomer(const std::string& id) {
    for (const auto& cust : customers_) {
        if (cust.GetID() == id) {
            return cust;
        }
    }
    // Return dummy customer if not found
    return Customer("", "");
}