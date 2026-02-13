#ifndef ELEC_AS_CPP_CUSTOMER
#define ELEC_AS_CPP_CUSTOMER

#include <string>
#include <vector>

#include "book.hpp"

class Customer {
 public:
  /**
   * \brief Construct a new Customer
   *
   * \param name the customer's name (reference to const string)
   * \param id the customer number (reference to const string)
   */
  Customer(const std::string& name, const std::string& id);

  /**
   * \brief Get the Customer's name as a string.
   */
  std::string GetName() const;

  /**
   * \brief Get the Customer's customer number as a string.
   */
  std::string GetID() const;

  /**
   * \brief Get the Customer's number of loans as an int.
   */
  int GetLoanAmount() const;

  /**
   * \brief Get the Customer's loans as a vector<Book>.
   */
  std::vector<Book> GetLoans() const;

  /**
   * \brief loans a book for the customer
   */
  bool LoanBook(Book& b);

  /**
   * \brief Returns a book loaned by the customer.
   */
  void ReturnBook(Book& b);

  /**
   * \brief write the customer's information to the standard output stream.
   */
  void Print() const;

 private:
  std::string name_;
  std::string id_;
  std::vector<Book> loans_;
};

#endif