#pragma once

#include <vector>

class customer_t {
  public:
    customer_t(std::vector<int>, std::vector<int>);
    customer_t();

  private:
    std::vector<int> initial_allocation;
    std::vector<int> request;
};

