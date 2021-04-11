#pragma once

#include <vector>
#include <pthread.h>

#include "../includes/customer_t.hpp"
#include "../includes/extended_vector_t.hpp"

class banker_t {
  public:
    banker_t(EVec::extended_vector_t<int>, std::vector<customer_t*>);
    banker_t();

    EVec::extended_vector_t<int> get_available_funds();
    // NOTE : what the hell is this? -> EVec::extended_vector_t<int> get_initial_request();

    void print();
    void update_avaialble_funds(EVec::extended_vector_t<int>);

    bool can_grant_request(EVec::extended_vector_t<int>);

    // FIXME
    void conduct_simulation();
    void withdrawl_resources(customer_t*);
    void deposit(customer_t*);

    void add_customers(std::vector<customer_t*>);

  private:
    //std::vector<int> available_funds;
    EVec::extended_vector_t<int> available_funds;
    std::vector<customer_t*> customers;
};

