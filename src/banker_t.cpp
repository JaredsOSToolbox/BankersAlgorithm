#include "../includes/banker_t.hpp"

#include <iostream>
#include <string>
#include <vector>

banker_t::banker_t(std::vector<int> container) {
  this->available_funds = container;
}

banker_t::banker_t(){
  this->available_funds = std::vector<int>();
}

std::vector<int> banker_t::get_available_funds(){
  return this->available_funds;
}

void banker_t::print(){
  std::cout << '[';
  for(auto element : this->available_funds){
    std::cout << element << ',';
  }
  std::cout << ']' << std::endl;
}

bool banker_t::can_grant_request(std::vector<int> container){
  if(container.size() != this->available_funds.size()){
    return false;
  }
  for(size_t i = 0; i < container.size(); ++i){
    if(container[i] >= this->available_funds[i]){
      return false;
    }
  }
  // TODO | incomplete
  return true;
}
