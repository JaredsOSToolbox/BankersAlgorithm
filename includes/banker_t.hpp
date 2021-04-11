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

    void update_avaialble_funds(EVec::extended_vector_t<int>);

    bool can_grant_request(int, EVec::extended_vector_t<int>);

    void conduct_simulation();
    void withdrawl_resources(customer_t*);
    void deposit(customer_t*);

    std::vector<customer_t*> get_customers() const;

    void add_customers(std::vector<customer_t*>);

    friend std::ostream& operator<<(std::ostream&, const banker_t&);

  private:
    //std::vector<int> available_funds;
    EVec::extended_vector_t<int> available_funds;
    std::vector<customer_t*> customers;
};

