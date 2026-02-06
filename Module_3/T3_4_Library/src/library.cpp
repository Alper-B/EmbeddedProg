#include "library.hpp"

Library::Library(const std::string& name) : name_(name) {}

std::string Library::GetName() const { return name_; }

std::vector<Book>& Library::GetBooks() { return books_; }
std::vector<Customer>& Library::GetCustomers() { return customers_; }

Book Library::FindBookByName(const std::string& name) {
  for (auto& b : books_) {
    if (b.GetName() == name) return b;
  }
  return Book("", "", "");
}

std::vector<Book> Library::FindBooksByAuthor(const std::string& name) {
  std::vector<Book> result;
  for (auto& b : books_) {
    if (b.GetAuthor() == name) result.push_back(b);
  }
  return result;
}

std::vector<Book> Library::FindAllLoanedBooks() {
  std::vector<Book> result;
  for (auto& b : books_) {
    if (b.GetStatus()) result.push_back(b);
  }
  return result;
}

Customer Library::FindCustomer(const std::string& id) {
  for (auto& c : customers_) {
    if (c.GetID() == id) return c;
  }
  return Customer("", "");
}
