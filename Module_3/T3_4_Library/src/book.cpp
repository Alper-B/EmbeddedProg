#include "book.hpp"
#include <iostream>

Book::Book(const std::string& name,
           const std::string& author,
           const std::string& isbn,
           bool loaned,
           Date due_date)
    : name_(name),
      author_(author),
      isbn_(isbn),
      loaned_(loaned),
      due_date_(due_date) {}

std::string Book::GetName() const { return name_; }
std::string Book::GetAuthor() const { return author_; }
std::string Book::GetISBN() const { return isbn_; }
bool Book::GetStatus() const { return loaned_; }
Date Book::GetDueDate() const { return due_date_; }

bool Book::Loan() {
  if (loaned_) return false;

  Date d = Date::Today();
  d.month += 1;
  if (d.month > 12) {
    d.month = 1;
    d.year += 1;
  }

  due_date_ = d;
  loaned_ = true;
  return true;
}

void Book::Restore() {
  loaned_ = false;
  due_date_ = {0, 0, 0};
}

void Book::Print() const {
  std::cout << "Book: " << name_
            << ", author: " << author_
            << ", ISBN: " <<
