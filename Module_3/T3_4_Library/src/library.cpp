#include "library.hpp"

#include <iostream>
#include <vector>

#include "book.hpp"
#include "customer.hpp"

Library::Library(const std::string& name) : name_(name) {}

std::string Library::GetName() const { return name_; }

std::vector<Book>& Library::GetBooks() { return books_; }

std::vector<Customer>& Library::GetCustomers() { return customers_; }

Book Library::FindBookByName(const std::string& name) {
  for (const auto& book : books_) {
    if (book.GetName() == name) {
      return book;
    }
  }
  // Return a new book with empty strings if not found
  return Book("", "", "");
}

std::vector<Book> Library::FindBooksByAuthor(const std::string& author) {
  std::vector<Book> found_books;
  for (const auto& book : books_) {
    if (book.GetAuthor() == author) {
      found_books.push_back(book);
    }
  }
  return found_books;
}

std::vector<Book> Library::FindAllLoanedBooks() {
  std::vector<Book> loaned_books;
  for (const auto& book : books_) {
    if (book.GetStatus()) {
      loaned_books.push_back(book);
    }
  }
  return loaned_books;
}

Customer Library::FindCustomer(const std::string& id) {
  for (const auto& customer : customers_) {
    if (customer.GetID() == id) {
      return customer;
    }
  }
  // Return new customer with empty strings if not found
  return Customer("", "");
}