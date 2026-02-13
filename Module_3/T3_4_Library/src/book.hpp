#ifndef ELEC_AS_CPP_BOOK
#define ELEC_AS_CPP_BOOK

#include <ctime>
#include <string>
#include <iostream>

/**
 * \brief Date structure
 *
 */
struct Date {
  int day;   /** The day of the date*/
  int month; /** The month of the date*/
  int year;  /** The year of the date*/

  /**
   * \brief Constructs a Date after setting its date field to local calendar
   * date of the computer.
   */
  static Date Today() {
    Date d;
    std::time_t t = time(0);
    struct tm* now = localtime(&t);
    d.day = now->tm_mday;
    d.month = now->tm_mon + 1;
    d.year = now->tm_year + 1900;
    return d;
  }
};

class Book {
 public:
  /**
   * \brief Construct a new Book object
   *
   * \param name the book's name (reference to const string),
   * \param author the book's author (reference to const string),
   * \param isbn the book's ISBN number (reference to const string)
   * \param loaned the status of the book, loaned or not (bool), which is by
   * default false
   * \param due_date due date as a Date structure (Date), which is by default
   * 0-0-0
   */
  Book(const std::string& name, const std::string& author,
       const std::string& isbn, bool loaned = false,
       Date due_date = {0, 0, 0});

  /**
   * \brief Get the Name of the book.
   */
  std::string GetName() const;

  /**
   * \brief Get the Book's author as a string.
   */
  std::string GetAuthor() const;

  /**
   * \brief Get the Book's ISBN as a string.
   */
  std::string GetISBN() const;

  /**
   * \brief Get the Book's status as a bool.
   */
  bool GetStatus() const;

  /**
   * \brief Get the Book's due date.
   */
  Date GetDueDate() const;

  /**
   * \brief Loans the book
   */
  bool Loan();

  /**
   * \brief Restores the book status to not loaned
   */
  void Restore();

  /**
   * \brief Prints the book's information to the standard output stream.
   */
  void Print() const;

 private:
  std::string name_;
  std::string author_;
  std::string isbn_;
  bool loaned_;
  Date due_date_;
};

#endif