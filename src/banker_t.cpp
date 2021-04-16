#include "../includes/banker_t.hpp"
#include "../includes/customer_t.hpp"
#include "../includes/extended_vector_t.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>


#define DEADLOCK 100

pthread_mutex_t mutex_;
banker_t banker_;

void* runner(void* parameters) {
  // FIXME
  customer_t* customer = (customer_t*)parameters;

  int i = 0;


  pthread_mutex_lock(&mutex_);
  printf("[INFO] Customer thread p#%d has started..\n", customer->get_number());
  //pthread_mutex_unlock(&mutex_);
  
  // NOTE : BORKED!
  while(!customer->needs_met() && i < DEADLOCK) {
    int index = customer->get_number();
    bool approved = banker_.can_grant_request(index, customer->get_request());

    if(approved) {
      printf("[APPROVED] Granting process %d the desired resources\n", index);
      banker_.withdrawl_resources(customer);
      std::cout << banker_ << std::endl;
    } else {
      printf("[DENIED] Will not grant process %d desired resources\n", index);
    }
    if(customer->needs_met()){
      printf("[RECIEVED] Process %d has been sataiated and will give its resources back\n", index);
      banker_.deposit(customer);
    }
    ++i;
  }
  
  //pthread_mutex_lock(&mutex_);
  printf("[INFO] Customer thread p#%d has completed..\n", customer->get_number());
  pthread_mutex_unlock(&mutex_);
  if(i < DEADLOCK){
    pthread_exit(EXIT_SUCCESS);
  } else {
    std::cerr << "[FATAL] Algorithm has entered a deadlocked state!" << std::endl;
    pthread_exit((void*)EXIT_FAILURE); // uhhh what's going on clang, are you drunk?
  }
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

template <typename T>
bool all(std::vector<T> container){
  for(bool element : container){
    if(!element){ return false; }
  }
  return true;
}

bool banker_t::can_grant_request(int index, EVec::extended_vector_t<int> request){
  /*
   * NOTE
   *
   * Algorithm taken from the lecture slides
  */

  size_t _n_procs = this->customers.size(); // number of processes
  size_t _m_resources = this->customers[0]->get_maximum().size(); // number of resources

  // Vector that notes if each process would have finished if given the proper resources
  std::vector<bool> finish(_n_procs, false);

  //  PRETEND TO ALLOCATE
  EVec::extended_vector_t<int> t_available = this->available_funds - request;
  // Variable we can manipulate throughout the for loop
  EVec::extended_vector_t<int> work = t_available;

  // Check the system to see if it's in a safe state
  for(size_t i = 0; i < _n_procs; ++i) {
    if (i == index) {
      continue;
    }  // don't process the same node twice (these nodes are essentially being
       // passed in by reference)
    
    // Current need of the process
    EVec::extended_vector_t<int> need_i = this->customers[i]->get_request();
    // Currently allocated resources
    // This vector gets updated if the process is given any resources
    EVec::extended_vector_t<int> allocation_i = this->customers[i]->get_init();

    // If the resource has a smaller resource footprint, then we can allow it
    // And if it does not exceed the available funds
    if (request <= need_i && request <= available_funds) {
      work -= request;          // decrease the amount of resources available

      // If the need of a given process is less than the available resources
      // say that this process is allowing the system to be in a safe state
      if (need_i <= work && finish[i] == false) {
        finish[i] = true;
        work += allocation_i;
      } 

      else { break; }
    } 
      else {
        // The process should automatically be denied resources
        // as it would put the system in an unsafe state
        return false;
      }
  }
  // if all processes will result in a safe state
  // we are okay
  return all(finish);
}

void banker_t::withdrawl_resources(customer_t* customer) {
  /*
   * Give resources to the customer
  */

  this->available_funds-=customer->get_request();
  customer->obtain_resources();
}

void banker_t::deposit(customer_t* customer) {

  /*
   * Take all resources from customer
  */

  this->available_funds+=customer->get_maximum();
  customer->drop_resources();
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
  std::cout << banker_ << std::endl;
}


void banker_t::add_customers(std::vector<customer_t*> container) {
  this->customers = container;
}

std::vector<customer_t*> banker_t::get_customers() const{
  return this->customers;
}

std::ostream& operator<<(std::ostream& os, const banker_t& banker){
  os << "Available: ";
  // FIXME
  print_vector(banker.available_funds.get_data());
  os << std::endl;

  os << "ALLOCATED\tMAXIMUM\t\tNEED" << std::endl;
  
  for(auto customer : banker.get_customers()) {
    os << *customer; 
  }
  return os;
}
