#include "../includes/banker_t.hpp"
#include "../includes/customer_t.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <pthread.h>

/*
 * outside the scope any class
 * and cannot be used in other parts of the codebase
*/

pthread_mutex_t mutex_; // not too sure where to put this for linking purposes

void* runner(void* parameters) {
  struct args_t* arguments = (struct args_t *)parameters;
  // FIXME
  //banker_t* banker = arguments->banker;
  //customer_t* customer = arguments->customer;

  pthread_mutex_lock(&mutex_);
// customer->get_threadid()
  printf("[INFO] Customer thread p#%d has started..", 69);
  pthread_mutex_unlock(&mutex_);

  /*
   * Some magical algo
  */

  // The infinite conditional while loop
  //while(!customer->needs_met()) {
    
  //}

  pthread_mutex_lock(&mutex_);
  // customer->get_threadid()
  printf("[INFO] Customer thread p#%d is shutting down...\n", 69);
  pthread_mutex_unlock(&mutex_);
  pthread_exit(EXIT_SUCCESS); 



}

banker_t::banker_t(std::vector<int> container) {
  this->available_funds = container;
}

banker_t::banker_t(){
  this->available_funds = std::vector<int>();
}

std::vector<int> banker_t::get_available_funds(){
  return this->available_funds;
}

// FIXME : same as constructor
void banker_t::update_avaialble_funds(std::vector<int> container){
  this->available_funds = container;
}

void banker_t::print(std::vector<customer_t> customers){
  std::cout << "Available: ";
  print_vector(this->available_funds);
  std::cout << std::endl;

  printf("ALLOCATED\tMAXIMUM\t\tNEED\n");
  
  for(customer_t customer : customers) {
    customer.print();
  }
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

void banker_t::conduct_simulation(std::vector<customer_t> customers) {
  pthread_attr_t attr;
  pthread_mutexattr_t mutex_attr;
  pthread_attr_init(&attr);
  pthread_mutexattr_init(&mutex_attr);
  pthread_mutex_init(&mutex_, &mutex_attr);

  // Create Threads
  //for(auto customer : customers) {
    //pthread_create(customer->get_threadid(), &attr, customer->runner, customer);
  //}

  // Join Threads
  //for(auto customer : customers) {
    //pthread_join(customer->get_threadid(), NULL);
  //}
}
