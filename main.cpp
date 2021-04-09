/*#include <iostream>*/

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

  reader_t source = reader_t("inputs/bankers_tiny.txt", &customers, &banker);

  return 0;
}
