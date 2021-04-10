#pragma once

#include <vector>

#include <pthread.h>

void print_vector(std::vector<int>);

class customer_t {
  public:
    customer_t(std::vector<int>, std::vector<int>, int);
    customer_t();

    int get_number();
    pthread_t* get_pthread_id();
    std::vector<int> get_maximum();

    std::vector<int> get_request();
    bool needs_met();

    //void* runner(void*);
  
    void print();


    void set_number(int); // test function to see if we can manipulate this class

    std::vector<int> initial_allocation; // FIXME: we are making it public so we can edit the values like a structure
    std::vector<int> request;
  private:
    std::vector<int> maximum;
    int number;

    pthread_t thread_id;
};

