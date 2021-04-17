#include "../includes/banker_t.hpp"
#include "../includes/customer_t.hpp"
#include "../includes/extended_vector_t.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>


#define MUTEX_SAFE(x) pthread_mutex_lock(&mutex_); \
                      x; \
                      pthread_mutex_unlock(&mutex_);

#define DEADLOCK 100

pthread_mutex_t mutex_;
banker_t banker_;

void* runner(void* parameters) {
  customer_t* customer = (customer_t*)parameters;

  int i = 0;

  MUTEX_SAFE(printf("[INFO] Customer thread p#%d has started..\n",
                    customer->get_number()))

  while (!customer->needs_met() && i < DEADLOCK) {
    int index = customer->get_number();
    bool approved = banker_.can_grant_request(index, customer->request());

    if (approved) {
      MUTEX_SAFE(printf(
          "[APPROVED] Granting process %d the desired resources\n", index))
      banker_.withdrawl_resources(customer);

      MUTEX_SAFE(std::cout << banker_ << std::endl)

      if (customer->needs_met()) {
        MUTEX_SAFE(
            printf("[RECIEVED] Process %d has been sataiated and will give its "
                   "resources back\n",
                   index))
        banker_.deposit(customer);
      }

    } else {
      MUTEX_SAFE(printf(
          "[DENIED] Will not grant process %d desired resources\n", index))
    }
    ++i;
  }

  MUTEX_SAFE(printf("[INFO] Customer thread p#%d has completed..\n",
                    customer->get_number());)
  if (i < DEADLOCK) {
    pthread_exit(EXIT_SUCCESS);
  } else {
    std::cerr << "[FATAL] Algorithm has entered a deadlocked state!"
              << std::endl;
    pthread_exit(
        (void*)EXIT_FAILURE);  // uhhh what's going on clang, are you drunk?
  }
}

banker_t::banker_t(EVec::extended_vector_t<int> container, std::vector<customer_t*> customers) {
  this->available_funds = container;
  this->customers = customers;
  this->_n_processes = customers.size();
  this->_m_resources = customers[0]->get_init().size();
}

banker_t::banker_t(){
  this->available_funds = EVec::extended_vector_t<int>();
  this->_n_processes = 0;
  this->_m_resources = 0;
}

EVec::extended_vector_t<int> banker_t::get_available_funds(){
  return this->available_funds;
}

// FIXME : same as constructor
void banker_t::update_avaialble_funds(EVec::extended_vector_t<int> container) {
  this->available_funds = container;
}

template <typename T>
// would be helpful to pass in a function pointer
bool all(EVec::extended_vector_t<T> container){
  for(T element : container.get_data()){
    if (element >= 0) {
      continue;
    } else {
      return false;
    }
  }
  return true;
}

template <typename T>

bool any_(EVec::extended_vector_t<T> container) {
  int i = 0;
  for(auto element : container.get_data()) {
    if(element){ i++; }
  }
  return (i > 0);
}

bool banker_t::is_safe(int index, EVec::extended_vector_t<int> request){
  // grant request temp
  // go through list of customers
  // are there enough resources for at least one customers to get it's max
  // roll back request
  
  EVec::extended_vector_t<int> total_available = this->available_funds - this->total_allocated;

  std::vector<bool> running(this->processes(), true);

  for(size_t i = 0; i < this->processes(); ++i) {
    bool at_least_one_allocated = false;
    for(size_t j = 0; j < this->processes(); ++j) {
     
     if(running[i]){
       auto _temp = total_available - (this->customers[j]->get_maximum() -
                                       this->customers[j]->get_init());
       if(all(_temp)){
         at_least_one_allocated = true;
         running[j] = false;
         total_available += this->customers[j]->get_init();
       }
     }

    }
    if(!at_least_one_allocated){ return false; }
  }
  return true;
}

bool banker_t::can_grant_request(int index, EVec::extended_vector_t<int> request){
  /*
   * NOTE
   *
   * Algorithm taken from the lecture slides
  */

  if(request > this->available_funds){ return false; }
  if (this->customers[index]->request_exceeds_needs()) {
    return false;
  }

  return this->is_safe(index, request);
}

void banker_t::withdrawl_resources(customer_t* customer) {
  /*
   * Give resources to the customer
  */

  this->available_funds-=customer->request();
  this->total_allocated+=customer->request();

  customer->obtain_resources();
}

void banker_t::deposit(customer_t* customer) {

  /*
   * Take all resources from customer
  */

  this->available_funds+=customer->get_maximum();
  this->total_allocated-=customer->get_maximum();

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
  
  banker_.finished = std::vector<bool>(this->customers.size(), false);
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

int banker_t::resources() const { return this->_m_resources; }
int banker_t::processes() const { return this->_n_processes; }

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
