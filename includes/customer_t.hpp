#pragma once

#include <vector>
#include "extended_vector_t.hpp"

#include <pthread.h>

// NOTE : cheesing this std::ostream hard
void print_vector(std::vector<int>);

class customer_t {
  public:
    //customer_t(std::vector<int>, std::vector<int>, int);
    customer_t(EVec::extended_vector_t<int>, EVec::extended_vector_t<int>, int);
    customer_t();

    int get_number();
    pthread_t* get_pthread_id();

    EVec::extended_vector_t<int> get_maximum();
    EVec::extended_vector_t<int> get_init();
    EVec::extended_vector_t<int> request();

    void generate_request();
    void clear_request();

    bool needs_met();
    bool request_exceeds_needs();

    void print();

    void drop_resources(); // deposit funds
    void obtain_resources(); // get funds from bank


    void set_number(int); // test function to see if we can manipulate this class

    friend std::ostream& operator<<(std::ostream&, const customer_t&);

  private:
    //std::vector<int> initial_allocation; // FIXME: we are making it public so we can edit the values like a structure
    //std::vector<int> request;
    //std::vector<int> maximum;

    EVec::extended_vector_t<int> initial_allocation, need, maximum, request_; // request is randomly generated
    int number;

    pthread_t thread_id;
};

