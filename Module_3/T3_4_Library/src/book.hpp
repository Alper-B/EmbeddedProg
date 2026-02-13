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
    bool Loan();   // Returns true if loan logic was successful (was not already loaned)
    void Restore(); // Sets status back to available

private:
    std::string name_;
    std::string author_;
    std::string isbn_;
    bool loaned_;
};

#endif