#pragma once

#include <vector>
#include <pthread.h>
#include "../includes/customer_t.hpp"

class banker_t {
  public:
    banker_t(std::vector<int>);
    banker_t();

    std::vector<int> get_available_funds();
    void print(std::vector<customer_t>);
    void update_avaialble_funds(std::vector<int>);

    bool can_grant_request(std::vector<int>);

    void conduct_simulation(std::vector<customer_t>*);

  private:
    std::vector<int> available_funds;
};

