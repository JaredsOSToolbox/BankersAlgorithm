#include <iostream>
#include <queue>

#include <stdio.h>

#include "includes/banker_t.hpp"
#include "includes/customer_t.hpp"
#include "includes/reader_t.hpp"


const char* AUTHOR = "Jared Dyreson";
const char* INSTITUTION = "California State University Fullerton";

void version(void) {
  printf(
      "bankruptcy (%s) 1.0\n"
      "Copyright (C) 2021 Comrade Software Foundation Inc.\n"
      "MIT License\n"
      "This is free software, and provided as is without warranty\n"
      "Written by %s",
      INSTITUTION, AUTHOR);
}

int main(void){

  banker_t banker = banker_t();
  std::vector<customer_t> customers;

  std::queue<customer_t> process_queue;

  reader_t source = reader_t("inputs/bankers_tiny.txt", &customers, &banker);
  
  banker.print(customers);
  banker.conduct_simulation(&customers);
  banker.print(customers);

  //for(auto element : customers) {
    //element.print();
  //}
  
  //while(!customers.empty()) {
    //auto customer = customers.pop_back();
    //if(!request_granted){
      //fprintf(stderr, "Process %d could not be granted\n", customer.get_number());
      //process_queue.push(customer);
    //}
  //}

  return 0;
}
