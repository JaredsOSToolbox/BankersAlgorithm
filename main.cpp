#include <iostream>
#include <queue>

#include <stdio.h>
#include <stdlib.h>
#include <filesystem>
#include <set>
#include <assert.h>

#include "includes/extended_vector_t.hpp"

#include "includes/banker_t.hpp"
#include "includes/customer_t.hpp"
#include "includes/reader_t.hpp"

#define TEST_COUNT 4

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

std::set<std::filesystem::path> get_tests(std::string origin) {
  /*
   * Sort by filename
   * Source:
   * https://stackoverflow.com/questions/62409409/how-to-make-stdfilesystemdirectory-iterator-to-list-filenames-in-order
   */

  std::set<std::filesystem::path> container;

  for (const auto& entry : std::filesystem::directory_iterator(origin)) {
    container.insert(entry.path());
  }

  return container;
}

template <typename T>
bool all(std::vector<T> container) {
  for(T element : container) {
    if(!element){ return false; }
  }
  return true;
}

void conduct_all(bool verbose) {

  std::vector<bool> iterations(TEST_COUNT, false); // we know how many tests there are

  std::set<std::filesystem::path> paths = get_tests("inputs/");

  int i = 0;

  for(auto& entry : paths) {
    const char* _path = entry.c_str();
    printf("[INFO] Conducting test on %s\n", _path);
    banker_t banker = banker_t();

    reader_t source = reader_t(_path, &banker);
    std::cout << banker << std::endl; 
    bool success = banker.conduct_simulation(verbose);
    iterations[i++] = success;
  }

  assert(all(iterations) == true);
  printf("[INFO] All %d assertions passed!\n", TEST_COUNT);
}


int main(int argc, const char* argv[]){
  //banker_t banker = banker_t();
  //const char* _path = "inputs/01_bankers_tiny.txt";
  //reader_t source = reader_t(std::string(_path), &banker);

  //std::cout << banker << std::endl;
  //bool success = banker.conduct_simulation(false);

  //printf("[%s] Finished %s\n", (success) ? "SUCCESS" : "FALIED", _path);
  conduct_all(false);
  return 0;
}
