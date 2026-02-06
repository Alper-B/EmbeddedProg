#include "library.hpp"

class Library {
 public:
  Library(const std::string& name);

  std::string GetName() const;
  std::vector<Book>& GetBooks();
  std::vector<Customer>& GetCustomers();

  Book FindBookByName(const std::string& name);
  std::vector<Book> FindBooksByAuthor(const std::string& name);
  std::vector<Book> FindAllLoanedBooks();
  Customer FindCustomer(const std::string& id);

 private:
  std::string name_;
  std::vector<Book> books_;
  std::vector<Customer> customers_;
};