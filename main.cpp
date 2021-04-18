#include <iostream>
#include <queue>

#include <stdio.h>
#include <stdlib.h>
#include <filesystem>

#include "includes/extended_vector_t.hpp"

#include "includes/banker_t.hpp"
#include "includes/customer_t.hpp"
#include "includes/reader_t.hpp"

namespace fs = std::filesystem;

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

void conduct_all(bool verbose) {

  std::string path = "inputs/";
  for(const auto& entry : fs::directory_iterator(path)) {
    const char* _path = entry.path().c_str();
    printf("[INFO] Conducting test on %s\n", _path);
    banker_t banker = banker_t();

    reader_t source = reader_t(entry.path(), &banker);
    std::cout << banker << std::endl; 
    bool success = banker.conduct_simulation(verbose);
    printf("[%s] Finished %s\n", (success) ? "SUCCESS" : "FALIED", _path);
  }
}


int main(int argc, const char* argv[]){
  //if(argc < 2){
    //usage();
    //return EXIT_FAILURE;
  //}
  conduct_all(false);
  //return 0;
  //banker_t banker = banker_t();

  //reader_t source = reader_t("inputs/bankers_medium.txt", &banker);
  //std::cout << banker << std::endl; 
  //banker.conduct_simulation();

  return 0;
}
