#include "../includes/banker_t.hpp"
#include "../includes/customer_t.hpp"
#include "../includes/extended_vector_t.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex_;
banker_t banker_;

void* runner(void* parameters) {
  // FIXME
  customer_t* customer = (customer_t*)parameters;


  pthread_mutex_lock(&mutex_);
  printf("[INFO] Customer thread p#%d has started..\n", customer->get_number());
  pthread_mutex_unlock(&mutex_);
  
  // NOTE : BORKED!
  while(!customer->needs_met()) {
    int index = customer->get_number();
    bool approved = banker_.can_grant_request(customer->get_request());

    if(approved) {
      printf("[APPROVED] Granting process %d the resources\n", index);
      banker_.withdrawl_resources(customer);
      banker_.print();
      std::cout << std::endl;
      //print_vector(banker_.get_available_funds());
    } else {
      printf("[DENIED] Will not grant process %d desired resources\n", index);
    }
    if(customer->needs_met()){
      printf("[RECIEVED] Process %d has given its resources back\n", index);
      banker_.deposit(customer);
    }
  }
  
  pthread_mutex_lock(&mutex_);
  printf("[INFO] Customer thread p#%d has completed..\n", customer->get_number());
  pthread_mutex_unlock(&mutex_);
  pthread_exit(EXIT_SUCCESS);
}

banker_t::banker_t(EVec::extended_vector_t<int> container, std::vector<customer_t*> customers) {
  this->available_funds = container;
  this->customers = customers;
}

banker_t::banker_t(){
  this->available_funds = EVec::extended_vector_t<int>();
  //this->customers = &std::vector<customer_t*>();
}

EVec::extended_vector_t<int> banker_t::get_available_funds(){
  return this->available_funds;
}

// FIXME : same as constructor
void banker_t::update_avaialble_funds(EVec::extended_vector_t<int> container) {
  this->available_funds = container;
}

void banker_t::print(){
  // FIXME
  // use std::ostream
  //return;

  std::cout << "Available: ";
  print_vector(this->available_funds.get_data());
  std::cout << std::endl;

  printf("ALLOCATED\tMAXIMUM\t\tNEED\n");
  
  for(auto customer : this->customers) {
    customer->print();
  }
}

bool banker_t::can_grant_request(EVec::extended_vector_t<int> request){
  // FIXME | incomplete
  return this->available_funds > request;
}

void banker_t::withdrawl_resources(customer_t* customer) {
  // TODO : give resources to customer

  this->available_funds-=customer->get_request();
  customer->obtain_resources();
}

void banker_t::deposit(customer_t* customer) {

  // TODO : take all resources from customer
  this->available_funds+=customer->get_maximum();
  customer->drop_resources();

  //for(size_t i = 0; i < available_funds.size(); ++i) {
    //int amount = customer->initial_allocation[i];
    //customer->initial_allocation[i]-=amount; // take the resources away from the process
    //this->available_funds[i]+=amount; // give them back to the bank
  //}
}

void banker_t::conduct_simulation() {
  printf("[INFO] Conducting the simulation...\n");

  pthread_t tid[customers.size()];

  pthread_attr_t attr;
  pthread_mutexattr_t mutex_attr;
  pthread_attr_init(&attr);
  pthread_mutexattr_init(&mutex_attr);
  pthread_mutex_init(&mutex_, &mutex_attr);

  banker_ = *this;

  // Create Threads
  int i = 0;
  for(auto customer : this->customers) {
    pthread_create(&tid[i++], &attr, runner, (void*)(customer_t*)customer);
  }

  // Join Threads
  i = 0;
  for(auto customer : this->customers) {
    pthread_join(tid[i++], NULL);
  }
}

void banker_t::add_customers(std::vector<customer_t*> container) {
  this->customers = container;
}
