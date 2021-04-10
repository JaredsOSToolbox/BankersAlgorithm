#include "../includes/extended_vector_t.hpp"

#include <vector>
#include <string>
#include <iostream>

// So I don't have to write this all out by hand

#define _T template <typename T>

/*
 * BEGIN CONSTRUCTORS
*/

_T

extended_vector_t<T>::extended_vector_t() : data(std::vector<T>()) {}

_T

extended_vector_t<T>::extended_vector_t(size_t size, const T& k){
  for(size_t i = 0; i < size; ++i){
    data.push_back(k);
  }
}

_T

extended_vector_t<T>::extended_vector_t(const std::vector<T>& container) : data(container) {}

_T

extended_vector_t<T>::extended_vector_t(const std::string& str, const std::initializer_list<T>& _list) : extended_vector_t() {
  for(const T& element : _list) {
    data.push_back(element);
  }
}

_T
extended_vector_t<T>::extended_vector_t(const std::initializer_list<T>& _list) : extended_vector_t<T>() {
  for(const T& element : _list) {
    data.push_back(element);
  }
}

/*
 * END CONSTRUCTORS
*/


/*
 * BEGIN CAPACITY FUNCTIONS
*/

_T

bool extended_vector_t<T>::empty() const {
  return data.empty();
}

_T

size_t extended_vector_t<T>::size() const {
  return data.size();
}

/*
 * END CAPACITY FUNCTIONS
*/

/*
 * BEGIN MODIFIER FUNCTIONS
*/

_T
void extended_vector_t<T>::push_back(T& element){
  data.push_back(element);
}

_T
void extended_vector_t<T>::clear(){
  data.clear();
}

/*
 * END MODIFIER FUNCTIONS
*/

/*
 * BEGIN OPERATOR FUNCTIONS
*/

_T

T extended_vector_t<T>::operator[](size_t i) const {
  return data[i];
}

_T

T& extended_vector_t<T>::operator[](size_t i) {
  return data[i];
}

_T

typename std::vector<T>::const_iterator extended_vector_t<T>::begin() const { 
  return data.begin(); 
}

_T

typename std::vector<T>::const_iterator extended_vector_t<T>::end() const { 
  return data.end(); 
}

_T

extended_vector_t<T>& extended_vector_t<T>::operator+=(const extended_vector_t<T>& other){
  for(size_t i = 0; i < other.data.size(); ++i) {
    data[i] += other.data[i];
  }
  return *this;
}

_T
extended_vector_t<T>& extended_vector_t<T>::operator-=(const extended_vector_t<T>& other){
  for(size_t i = 0; i < other.data.size(); ++i) {
    data[i] -= other.data[i];
  }
  return *this;
}

_T

extended_vector_t<T> extended_vector_t<T>::operator+(const extended_vector_t<T>& other) const {
  extended_vector_t<T> temp(data);
  temp += other;
  return temp;
}

_T
extended_vector_t<T> extended_vector_t<T>::operator-(const extended_vector_t<T>& other) const {
  extended_vector_t<T> temp(data);
  temp -= other;
  return temp;
}

_T
extended_vector_t<T> extended_vector_t<T>::operator*(const T& k) const {
  extended_vector_t<T> temp(data);

  for(size_t i = 0; i < data.size(); ++i) {
    temp.data[i] *= k;
  }
  return temp;
}

// FIXME : FRIENDS

//extended_vector_t<T> extended_vector_t<T>::operator*(const T& k, const extended_vector_t<T>& other) {
  //extended_vector_t<T> temp(other.data);

  //for(size_t i = 0; i < temp.size(); ++i) {
    //temp.data[i] *= k;
  //}
  //return temp;
//}

_T
bool extended_vector_t<T>::operator<(const extended_vector_t<T>& other) const {
  return data < other.data;
}

_T
bool extended_vector_t<T>::operator<=(const extended_vector_t<T>& other) const {
  return data <= other.data;
}

_T
bool extended_vector_t<T>::operator>(const extended_vector_t<T>& other) const {
  return data > other.data;
}

_T
bool extended_vector_t<T>::operator>=(const extended_vector_t<T>& other) const {
  return data >= other.data;
}

_T
bool extended_vector_t<T>::operator==(const extended_vector_t<T>& other) const {
  return data == other.data;
}

_T
bool extended_vector_t<T>::operator!=(const extended_vector_t<T>& other) {
  return !operator==(other);
}

_T
std::ostream& operator<<(std::ostream& os, const extended_vector_t<T>& vect) {
  if (vect.empty()) { return os << "[WARNING] extended_vector_t is empty\n"; }
  size_t i = 0;
  for (const T& element : vect.data) {
    os << std::setw(2) << element;
    if (i++ < vect.data.size() - 1) { os << " "; }
  }
  return os;
}
/*
 * END OPERATOR FUNCTIONS
*/
