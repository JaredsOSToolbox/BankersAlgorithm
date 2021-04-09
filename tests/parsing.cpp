#include <ctype.h>
#include <string>
#include <iostream>
#include <vector>

#define SPACES 3
const char delimiter = ',';

int main(void) {
  std::string line = "9, 9";
  std::vector<std::vector<int>> resources;

  // create temp char*
  const char* temp = line.c_str();

  int i = 0;  // how many spaces we have encountered during the parsing phase
  std::vector<int> p;
  

  while (*temp != '\0') {
    if (i == SPACES) {
      // stop counting and refresh
      printf("\n");
      i = 0;
      std::cout << "adding to resources" << std::endl;
      resources.push_back(p);
      p.clear();
    }

    if (isspace(*temp)) {
      std::cout << "got a space" << std::endl;
      ++i;
    } else {
      // reset if we found match
      i = 0;
      if (*temp != delimiter) {
        p.push_back((int)*temp - '0');
      }
    }

    temp++;
  }
  if(resources.size() == 0 && p.size() > 0){
    resources.push_back(p);
  }

  for(auto resource : resources) {
    for(auto element : resource){
      std::cout << element << ' ';
    }
    std::cout << std::endl;
  }

  std::cout << resources.size() << std::endl;
  return 0;
}
