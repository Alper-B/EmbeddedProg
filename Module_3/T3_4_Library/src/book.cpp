#include "book.hpp"

Book::Book(const std::string& name, const std::string& author, const std::string& isbn)
    : name_(name), author_(author), isbn_(isbn), loaned_(false) {
}

std::string Book::GetName() const { return name_; }
std::string Book::GetAuthor() const { return author_; }
std::string Book::GetISBN() const { return isbn_; }
bool Book::GetStatus() const { return loaned_; }

void Book::Print() const {
    std::cout << "Book: " << name_ << ", author: " << author_ 
              << ", ISBN: " << isbn_ 
              << ", loaned: " << (loaned_ ? "true" : "false") << std::endl;
}

bool Book::Loan() {
    if (loaned_) {
        return false;
    }
    loaned_ = true;
    return true;
}

void Book::Restore() {
    loaned_ = false;
}