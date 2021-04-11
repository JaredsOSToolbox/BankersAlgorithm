#pragma once

/*
 * ext_vector class from William McCarthy
 * However this is an adaptation of such implementation
 * This will allow us to more easily manipulate vectors
 * And will help with implementation of the banker's algorithm
*/

#include <string>
#include <vector>
#include <iostream>
#include <iomanip>

// So I don't have to write this all out by hand

#define _T template <typename T>

namespace EVec {
  _T

  class extended_vector_t {
    public:

      /*
       * Constructors
      */

      extended_vector_t();
      extended_vector_t(size_t, const T&);

      extended_vector_t(const std::vector<T>&);
      extended_vector_t(const std::string&, const std::initializer_list<T>&);

      extended_vector_t(const std::initializer_list<T>&);

      /*
       * Capacity functions
      */

      bool empty() const;
      size_t size() const;

      /*
       * Modifiers
      */

      void push_back(T);
      void clear();

      /*
       * Operators
      */

      T operator[](size_t) const;
      T& operator[](size_t);

      extended_vector_t& operator+=(const extended_vector_t<T>&);
      extended_vector_t& operator-=(const extended_vector_t<T>&);

      extended_vector_t operator-(const extended_vector_t<T>&) const;
      extended_vector_t operator+(const extended_vector_t<T>&) const;

      extended_vector_t operator*(const T&) const;

      friend extended_vector_t operator*(const T&, const extended_vector_t<T>&);

      bool operator<(const extended_vector_t<T>&) const;
      bool operator<=(const extended_vector_t<T>&) const;

      bool operator>(const extended_vector_t<T>&) const;
      bool operator>=(const extended_vector_t<T>&) const;

      bool operator==(const extended_vector_t<T>&) const;
      bool operator!=(const extended_vector_t<T>&);

      friend std::ostream& operator<<(std::ostream&, const extended_vector_t&);

      /*
       * Iterators
      */

      typename std::vector<T>::const_iterator begin() const;
      typename std::vector<T>::const_iterator end()   const;




    private:
      std::vector<T> data;
  };
}

#include "extended_vector_t.tcc"
