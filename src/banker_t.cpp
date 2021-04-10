#include "../includes/banker_t.hpp"
#include "../includes/customer_t.hpp"
#include "../includes/args_t.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex_; // not too sure where to put this for linking purposes

void* runner(void* parameters) {
  // FIXME
  struct args_t* params = (struct args_t *)parameters;

  banker_t* banker = params->banker;
  customer_t* customer = params->customer;

  pthread_mutex_lock(&mutex_);
  printf("[INFO] Customer thread p#%d has started..\n", customer->get_number());
  pthread_mutex_unlock(&mutex_);
  
  while(!customer->needs_met()) {
    int index = customer->get_number();
    bool approved = banker->can_grant_request(customer->get_request());

    if(approved) {
      banker->withdrawl_resources(customer);
      // banker->print();
    }
    if(customer->needs_met()){
      banker->deposit(customer);
      // banker->print();
    }
  }
  pthread_mutex_lock(&mutex_);
  printf("[INFO] Customer thread p#%d has completed..\n", customer->get_number());
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

void banker_t::print(std::vector<customer_t*> customers){
  std::cout << "Available: ";
  print_vector(this->available_funds);
  std::cout << std::endl;

  printf("ALLOCATED\tMAXIMUM\t\tNEED\n");
  
  for(auto customer : customers) {
    customer->print();
  }
}

bool banker_t::can_grant_request(std::vector<int> container){
  if(container.size() != this->available_funds.size()){
    return false;
  }
  for(size_t i = 0; i < container.size(); ++i){
    if(container[i] > this->available_funds[i]){
      return false;
    }
  }
  // TODO | incomplete
  return true;
}

void banker_t::withdrawl_resources(customer_t* customer) {
  std::vector<int> request = customer->get_request();

  for(size_t i = 0; i < available_funds.size(); ++i) {
    int amount = this->available_funds[i];
    this->available_funds[i]-=request[i]; // remove from the bank
    customer->initial_allocation[i]+=amount; // give to the process
  }
}

void banker_t::deposit(customer_t* customer) {

  for(size_t i = 0; i < available_funds.size(); ++i) {
    int amount = customer->initial_allocation[i];
    customer->initial_allocation[i]-=amount; // take the resources away from the process
    this->available_funds[i]+=amount; // give them back to the bank
  }
}

void banker_t::conduct_simulation(std::vector<customer_t*>* customers) {
  printf("[INFO] Conducting the simulation...\n");

  pthread_t tid[customers->size()];

  pthread_attr_t attr;
  pthread_mutexattr_t mutex_attr;
  pthread_attr_init(&attr);
  pthread_mutexattr_init(&mutex_attr);
  pthread_mutex_init(&mutex_, &mutex_attr);

  struct args_t* arguments = (struct args_t*)malloc(sizeof(struct args_t));
  arguments->banker = this; // NOTE : how this is legal is beyond me
  // NOTE: arguments->banker->print(*customers);

  // Create Threads
  int i = 0;
  for(auto customer : *customers) {
    arguments->customer = customer;
    pthread_create(&tid[i++], &attr, runner, arguments);
  }

  // Join Threads
  i = 0;
  for(auto customer : *customers) {
    pthread_join(tid[i++], NULL);
  }
}
