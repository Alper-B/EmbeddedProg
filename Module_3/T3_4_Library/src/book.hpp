#ifndef BOOK_HPP
#define BOOK_HPP

#include <string>
#include <iostream>

class Book {
public:
    // Constructor
    Book(const std::string& name, const std::string& author, const std::string& isbn);

    // Getters
    std::string GetName() const;
    std::string GetAuthor() const;
    std::string GetISBN() const;
    bool GetStatus() const;

    // Operations
    void Print() const;
    bool Loan();    // Returns true if loan successful, false if already loaned
    void Restore(); // Returns book (sets status to false)

private:
    std::string name_;
    std::string author_;
    std::string isbn_;
    bool loaned_;
};

#endif