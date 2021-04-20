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



int main(int argc, const char* argv[]){
  //conduct_all(false);
  std::vector<bool> example(4, true);
  bool _resultant = Utils::all(example);
  printf("%s\n", (_resultant) ? "true" : "false");
  return 0;
}
