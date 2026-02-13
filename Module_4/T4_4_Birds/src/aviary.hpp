#ifndef AALTO_ELEC_CPP_AVIARY_CLASS
#define AALTO_ELEC_CPP_AVIARY_CLASS

#include <iostream>
#include <vector>
#include <stdexcept>
#include "bird.hpp"

/**
 * \brief Class for storing different birds and interacting with them.
 */
class Aviary {
 public:
  Aviary() {}

  // Disallow copying
  Aviary(const Aviary&) = delete;
  Aviary& operator=(const Aviary&) = delete;

  /**
   * \brief method Add adds the given bird to the aviary.
   * \param bird A pointer to a bird object.
   */
  void Add(Bird* bird);

  /**
   * \brief method SpeakAll calls the Speak method on all birds in the aviary.
   * \param os A reference to the desired ostream.
   */
  void SpeakAll(std::ostream& os) const;

  /**
   * \brief method Size returns the number of birds in the aviary.
   * \return How many birds there are in the aviary.
   */
  size_t Size() const;

  /**
   * \brief non-const version of the indexing operator [].
   * \param idx desired index as an size_t integer value.
   * \return A pointer to the bird (Bird*) at the index given as an argument
   */
  Bird* operator[](size_t idx);

  /**
   * \brief const version of the indexing operator [].
   * \param idx desired index as an size_t integer value.
   * \return A pointer to the bird (const Bird*) at the index given as an
   * argument
   */
  const Bird* operator[](size_t idx) const;

  /**
   * \brief destructor. Takes no parameters.
   */
  ~Aviary();

 private:
  std::vector<Bird*> birds_;
};

#endif