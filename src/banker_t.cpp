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

// Preprocessor derectives are neat-o!

#define MUTEX_SAFE(x) pthread_mutex_lock(&mutex_); \
                      x; \
                      pthread_mutex_unlock(&mutex_);

pthread_mutex_t mutex_;
banker_t banker_;

void* runner(void* parameters) {
  customer_t* customer = (customer_t*)parameters;

  int i = 0;

  MUTEX_SAFE(printf("[INFO] Customer thread p#%d has started..\n",
                    customer->get_number()))


  while(!customer->needs_met() && i < DEADLOCK) {
    int index = customer->get_number();
    bool approved = banker_.can_grant_request(index, customer->get_request());

    if(approved) {
      MUTEX_SAFE(printf(
          "[APPROVED] Granting process %d the desired resources\n", index))
      banker_.withdrawl_resources(customer);

      MUTEX_SAFE(std::cout << banker_ << std::endl)

      if(customer->needs_met()){
        MUTEX_SAFE(
            printf("[RECIEVED] Process %d has been sataiated and will give its "
                   "resources back\n",
                   index))
        banker_.deposit(customer);
      }

    } 
    else {
      MUTEX_SAFE(printf(
          "[DENIED] Will not grant process %d desired resources\n", index))
    }
    ++i;
  }
  //pthread_mutex_unlock(&mutex_);
  
  // NOTE : BORKED!
  //bool cust_need_met = false; 
  ////while(!customer->needs_met() && i < DEADLOCK) {
  //while(!cust_need_met && i < DEADLOCK) {
    //int index = customer->get_number();
    ////bool approved = banker_.can_grant_request(index, customer->get_request());
    //cust_need_met = true; // FIXME | NAIVE, assume we get the resource

    //if(cust_need_met) {
    ////if(approved) {
      //printf("[APPROVED] Granting process %d the desired resources\n", index);
      ////banker_.withdrawl_resources(customer);
      //std::cout << banker_ << std::endl;
    //} else {
      //printf("[DENIED] Will not grant process %d desired resources\n", index);
    //}
    ////if(customer->needs_met()){
      ////printf("[RECIEVED] Process %d has been sataiated and will give its resources back\n", index);
      ////banker_.deposit(customer);
    ////}
    //++i;
  //}

  MUTEX_SAFE(printf("[INFO] Customer thread p#%d has completed..\n",
                    customer->get_number());)
  //pthread_mutex_lock(&mutex_);
  //pthread_mutex_unlock(&mutex_);

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
  this->finished = std::vector<bool>(customers.size(), false);
}

banker_t::banker_t(){
  this->available_funds = EVec::extended_vector_t<int>();
  this->finished = std::vector<bool>(customers.size(), false);
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
  for(T element : container){
    if(!element){ return false; }
  }
  return true;
}

template <typename T>

void fill(std::vector<T> container, T k) {
  for(size_t i = 0; i < container.size(); ++i) {
    container[i] = k;
  }
}

bool banker_t::can_grant_request(int index, EVec::extended_vector_t<int> request){
  /*
   * NOTE
   *
   * Algorithm taken from the lecture slides
  */

  if(request > this->available_funds){
    // if we exceed the available resources, this is an automatic denial of service
    return false;
  }

  // NOTE : SAFETY ALGORITHM

  size_t _n_procs = this->customers.size(); // number of processes
  size_t _m_resources = this->customers[0]->get_maximum().size(); // number of resources

  //  PRETEND TO ALLOCATE
  
  /*
   * Available = Available - Request(i) [t_available]
   * Allocation(i) = Allocation(i) + Request(i) [NOTE : NOT DONE HERE]
   * Need(i) = Need(i) - Request(i)
  */

  EVec::extended_vector_t<int> t_available = this->available_funds - request;
  //
  //EVec::extended_vector_t<int> work = this->available_funds - request;

  // Check the system to see if it's in a safe state
  size_t i;
  for(i = 0; i < _n_procs; ++i) {
    if (i == index) {
      // assume that the current process is safe
      this->finished[i] = true;
      continue;
    }
    // Current need of the process
    
    EVec::extended_vector_t<int> need_i = this->customers[i]->get_request();
    // Currently allocated resources
    // This vector gets updated if the process is given any resources
    
    EVec::extended_vector_t<int> allocation_i = this->customers[i]->get_init();

    
    // If the resource has a smaller resource footprint, then we can allow it
    // And if it does not exceed the available funds

    if (need_i <= work && !this->finished[i]) {
      

      this->finished[i] = true;
      work+=allocation_i;

      // If the need of a given process is less than the available resources
      // say that this process is allowing the system to be in a safe state
    } 
    else {
      // The process should automatically be denied resources
      // as it would put the system in an unsafe state
      return false;
    }
  }
  
  // if all processes will result in a safe state
  // we are okay, else we are not
  bool _all = all(this->finished);
  fill(this->finished, false); // reset the finished states for the next iteration
  return _all;
}

void banker_t::withdrawl_resources(customer_t* customer) {
  /*
   * Give resources to the customer
  */
  EVec::extended_vector_t<int> customer_request = customer->get_request();

  if(customer_request < this->available_funds) {
    this->available_funds -= customer_request;
    customer->obtain_resources();
    this->total_allocated+=customer_request;
  } else {
    MUTEX_SAFE(
        printf("[DENIED] Customer thread p#%d has been denied request..\n",
               customer->get_number()))
  }
  this->available_funds-=customer->get_request();
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
  
  this->finished = std::vector<bool>(this->customers.size(), false);
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
