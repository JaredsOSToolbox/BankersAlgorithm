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
#include "includes/utils.hpp"


int main(int argc, const char* argv[]) {
  if(argc < 2) {
    std::cout << "Conducting all tests by default" << std::endl;
    Utils::conduct_all(false);
  } else {
    std::vector<bool> s(4); // an artifact from conduct_all_tests
    Utils::conduct_certain_test(false, std::string(argv[1]), &s, 0);
  }
  return 0;
}
