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

#define MAX_TEST_ITERATIONS 1000



int main(int argc, const char* argv[]){
  //std::vector<bool> _container(1, false);
  //Utils::conduct_certain_test(false, "inputs/01_bankers_tiny.txt", &_container, 0);
  Utils::conduct_all(false);
  return 0;
}
