#pragma once

#include <vector>

class banker_t {
  public:
    banker_t(std::vector<int>);
    banker_t();

    std::vector<int> get_available_funds();
    void print();

    bool can_grant_request(std::vector<int>);

  private:
    std::vector<int> available_funds;
};

