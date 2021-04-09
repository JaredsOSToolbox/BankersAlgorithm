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
    bool needs_met();

    //void* runner(void*);
  
    void print();


    void set_number(int); // test function to see if we can manipulate this class
  private:
    std::vector<int> initial_allocation;
    std::vector<int> maximum;
    std::vector<int> request;
    int number;

    pthread_t thread_id;
};

