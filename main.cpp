#include <iostream>
#include <queue>

#include <stdio.h>
#include <stdlib.h>

#include "includes/extended_vector_t.hpp"

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

void usage(void) {
  std::cout << "usage: bankruptcy <input>" << std::endl;
}


int main(int argc, const char* argv[]){

  //if(argc < 2){
    //usage();
    //return EXIT_FAILURE;
  //}

  banker_t banker = banker_t();

  reader_t source = reader_t("inputs/bankers_tiny.txt", &banker);
  //reader_t source = reader_t(std::string(argv[1]), &banker);
  
  //reader_t source = reader_t("inputs/bankers_tiny.txt", &customers, &banker);
  
  //banker.print(customers);
  std::cout << banker << std::endl; 
  banker.conduct_simulation();

  //banker.print(customers);

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
