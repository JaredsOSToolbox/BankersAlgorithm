//#include "../includes/banker_t.hpp"
#include "../includes/customer_t.hpp"
#include "../includes/extended_vector_t.hpp"

#include <vector>
#include <iostream>

#include <stdio.h> // for printf
#include <stdlib.h>  // for EXIT_SUCCESS


void print_vector(std::vector<int> container) {
  std::cout << '[';
  for(size_t i = 0; i < container.size(); ++i){
    if(i+1 < container.size()){
      std::cout << container[i] << ' ';
    } else {
      std::cout << container[i];
    }
  }
  std::cout << ']';
}


customer_t::customer_t(EVec::extended_vector_t<int> init, EVec::extended_vector_t<int> request, int number){
//customer_t::customer_t(std::vector<int> init, std::vector<int> request, int number){
  this->initial_allocation = init;
  this->request = request;
  this->maximum = this->get_maximum();
  this->number = number;
}

customer_t::customer_t() {
  // default is set to 3 resources
  this->initial_allocation = EVec::extended_vector_t<int>({0, 0, 0});
  this->request = EVec::extended_vector_t<int>({0, 0, 0}); 
  this->maximum = EVec::extended_vector_t<int>({0, 0, 0});

  this->number = -1;
}

int customer_t::get_number() {
  return this->number;
}

EVec::extended_vector_t<int> customer_t::get_request(){
  return this->request;
}

bool customer_t::needs_met(){
  return (this->initial_allocation == this->maximum);
}

EVec::extended_vector_t<int> customer_t::get_maximum(){
  return this->initial_allocation + this->request;
  //EVec::extended_vector_t<int> maximum;
  //for(size_t i = 0; i < this->initial_allocation.size(); ++i){
    //maximum.push_back(this->initial_allocation[i] + this->request[i]);
  //}
  //return maximum;
}


void customer_t::print() {
  // FIXME
  return;
  //print_vector(this->initial_allocation);
  //std::cout << "\t\t";
  //print_vector(this->maximum);
  //std::cout << "\t\t";
  //print_vector(this->request); // need
  //std::cout << std::endl;
}

pthread_t* customer_t::get_pthread_id(){ return &thread_id; }


void customer_t::set_number(int number){
  this->number = number;
}
