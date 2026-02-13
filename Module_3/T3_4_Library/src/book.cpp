#include "book.hpp"

// Constructor
Book::Book(const std::string& name, const std::string& author, const std::string& isbn)
    : name_(name), author_(author), isbn_(isbn), loaned_(false) {
}

// Getters
std::string Book::GetName() const { return name_; }
std::string Book::GetAuthor() const { return author_; }
std::string Book::GetISBN() const { return isbn_; }
bool Book::GetStatus() const { return loaned_; }

// Print book details to stdout
void Book::Print() const {
    std::cout << "Book: " << name_ << ", author: " << author_ 
              << ", ISBN: " << isbn_ 
              << ", loaned: " << (loaned_ ? "true" : "false") << std::endl;
}

// Attempt to loan the book
bool Book::Loan() {
    if (loaned_) {
        return false; // Already loaned
    }
    loaned_ = true;
    return true;
}

// Return the book (restore availability)
void Book::Restore() {
    loaned_ = false;
}