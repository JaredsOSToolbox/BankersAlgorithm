#include <vector>
#include <string>
#include <iostream>


/*
 * BEGIN CONSTRUCTORS
*/

#define _U template <typename U>

namespace EVec {
  _U

  extended_vector_t<U>::extended_vector_t() : data(std::vector<U>()) {}

  _U

  extended_vector_t<U>::extended_vector_t(size_t size, const U& k){
    for(size_t i = 0; i < size; ++i){
      data.push_back(k);
    }
  }

  _U

  extended_vector_t<U>::extended_vector_t(const std::vector<U>& container) : data(container) {}

  _U

  extended_vector_t<U>::extended_vector_t(const std::string& str, const std::initializer_list<U>& _list) : extended_vector_t() {
    for(const U& element : _list) {
      data.push_back(element);
    }
  }

  _U
  extended_vector_t<U>::extended_vector_t(const std::initializer_list<U>& _list) : extended_vector_t<U>() {
    for(const U& element : _list) {
      data.push_back(element);
    }
  }

  /*
   * END CONSTRUCTORS
  */


  /*
   * BEGIN CAPACITY FUNCTIONS
  */

  _U

  bool extended_vector_t<U>::empty() const {
    return data.empty();
  }

  _U

  size_t extended_vector_t<U>::size() const {
    return data.size();
  }

  _U
  bool extended_vector_t<U>::any_() const {
    int i = 0;
    for(U element : this->data) {
      if(element){ i++; }
    }
    return (i > 0);
  }

  _U
  bool extended_vector_t<U>::all_() const {
    for(U element : this->data) {
      if (!element) {
        return false;
      }  // NOTE : must have a comparator operator with a boolean in their class
         // definition. Same applies to any_ function
    }
    return true;
  }

  /*
   * END CAPACITY FUNCTIONS
  */

  /*
   * BEGIN MODIFIER FUNCTIONS
  */

  _U
  void extended_vector_t<U>::push_back(U element){
    data.push_back(element);
  }

  _U
  void extended_vector_t<U>::clear(){
    data.clear();
  }

  /*
   * END MODIFIER FUNCTIONS
  */

  /*
   * BEGIN OPERATOR FUNCTIONS
  */

  _U

  U extended_vector_t<U>::operator[](size_t i) const {
    return data[i];
  }

  _U

  U& extended_vector_t<U>::operator[](size_t i) {
    return data[i];
  }

  _U

  typename std::vector<U>::const_iterator extended_vector_t<U>::begin() const { 
    return data.begin(); 
  }

  _U

  typename std::vector<U>::const_iterator extended_vector_t<U>::end() const { 
    return data.end(); 
  }

  _U

  extended_vector_t<U>& extended_vector_t<U>::operator+=(const extended_vector_t<U>& other){
    for(size_t i = 0; i < other.data.size(); ++i) {
      data[i] += other.data[i];
    }
    return *this;
  }

  _U
  extended_vector_t<U>& extended_vector_t<U>::operator-=(const extended_vector_t<U>& other){
    for(size_t i = 0; i < other.data.size(); ++i) {
      data[i] -= other.data[i];
    }
    return *this;
  }

  _U

  extended_vector_t<U> extended_vector_t<U>::operator+(const extended_vector_t<U>& other) const {
    extended_vector_t<U> temp(data);
    temp += other;
    return temp;
  }

  _U
  extended_vector_t<U> extended_vector_t<U>::operator-(const extended_vector_t<U>& other) const {
    extended_vector_t<U> temp(data);
    temp -= other;
    return temp;
  }

  _U
  extended_vector_t<U> extended_vector_t<U>::operator*(const U& k) const {
    extended_vector_t<U> temp(data);

    for(size_t i = 0; i < data.size(); ++i) {
      temp.data[i] *= k;
    }
    return temp;
  }

  // FIXME : FRIENDS

  //extended_vector_t<U> extended_vector_t<U>::operator*(const U& k, const extended_vector_t<U>& other) {
    //extended_vector_t<U> temp(other.data);

    //for(size_t i = 0; i < temp.size(); ++i) {
      //temp.data[i] *= k;
    //}
    //return temp;
  //}

  _U
  bool extended_vector_t<U>::operator<(const extended_vector_t<U>& other) const {
    return data < other.data;
  }

  _U
  bool extended_vector_t<U>::operator<=(const extended_vector_t<U>& other) const {
    return data <= other.data;
  }

  _U
  bool extended_vector_t<U>::operator>(const extended_vector_t<U>& other) const {
    return data > other.data;
  }

  _U
  bool extended_vector_t<U>::operator>=(const extended_vector_t<U>& other) const {
    return data >= other.data;
  }

  _U
  bool extended_vector_t<U>::operator==(const extended_vector_t<U>& other) const {
    return data == other.data;
  }

  _U
  bool extended_vector_t<U>::operator!=(const extended_vector_t<U>& other) {
    return !operator==(other);
  }

  _U

  std::ostream& operator<<(std::ostream& os, const extended_vector_t<U>& vect) {
    if (vect.empty()) { return os << "[WARNING] extended_vector_t is empty\n"; }
    size_t i = 0;
    for (const U& element : vect.data) {
      os << std::setw(2) << element;
      if (i++ < vect.data.size() - 1) { os << " "; }
    }
    return os;
  }
  /*
   * END OPERATOR FUNCTIONS
  */

  _U

  std::vector<U> extended_vector_t<U>::get_data() const { return this->data; }
}
