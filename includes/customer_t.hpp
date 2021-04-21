#pragma once

#include <vector>
#include "extended_vector_t.hpp"

// NOTE : cheesing this std::ostream hard
void print_vector(std::vector<int>);

class customer_t {
  public:
    customer_t(EVec::extended_vector_t<int>, EVec::extended_vector_t<int>, int);
    customer_t();

    int get_number();
    EVec::extended_vector_t<int> get_maximum();
    EVec::extended_vector_t<int> get_init();
    EVec::extended_vector_t<int> request();

    void generate_request();

    bool needs_met();

    void print();

    void drop_resources(); // deposit funds
    void obtain_resources(); // get funds from bank


    void set_number(int); // test function to see if we can manipulate this class

    friend std::ostream& operator<<(std::ostream&, const customer_t&);

  private:
    EVec::extended_vector_t<int> initial_allocation, request_, need, maximum;
    int number;

};

