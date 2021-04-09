#include "../includes/customer_t.hpp"

#include <vector>


customer_t::customer_t(std::vector<int> init, std::vector<int> request){
  this->initial_allocation = init;
  this->request = request;
}

customer_t::customer_t() {
  // default is set to 3 resources
  this->initial_allocation = std::vector<int>{{0, 0, 0}}; // I have never seen this instantation before in my life
  this->request = std::vector<int>{{0, 0, 0}};
}
