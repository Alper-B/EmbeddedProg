#ifndef ELEC_AS_CPP_LIBRARY
#define ELEC_AS_CPP_LIBRARY

#include <string>
#include <vector>

#include "book.hpp"
#include "customer.hpp"

class Library {
 public:
  /**
   * \brief Construct a new Library object
   *
   * \param name the library's name (const reference to string)
   */
  Library(const std::string& name);

  /**
   * \brief Get the library's name as a string.
   */
  std::string GetName() const;

  /**
   * \brief Get the Library's books as a reference to a vector<Book>.
   */
  std::vector<Book>& GetBooks();

  /**
   * \brief Get the Library's customers as a reference to a vector<Customer>.
   */
  std::vector<Customer>& GetCustomers();

  /**
   * \brief Searches for a book by its name.
   */
  Book FindBookByName(const std::string& name);

  /**
   * \brief Searches for books by their author.
   */
  std::vector<Book> FindBooksByAuthor(const std::string& author);

  /**
   * \brief Returns a vector of loaned Books.
   */
  std::vector<Book> FindAllLoanedBooks();

  /**
   * \brief Searches for a customer with specfied id
   */
  Customer FindCustomer(const std::string& id);

 private:
  std::string name_;
  std::vector<Book> books_;
  std::vector<Customer> customers_;
};

#endif