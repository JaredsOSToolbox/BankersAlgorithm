/*
 * FIXME : inserting into the vectors of vectors
*/

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
  int j = 0;  // position inside the resources buffer

  while (*temp != '\0') {
    if (i == SPACES) {
      // stop counting and refresh
      printf("\n");
      i = 0;
      ++j;
      k = 0;
    }

    if (isspace(*temp)) {
      ++i;
    } else {
      // reset if we found match
      i = 0;
      if (*temp != delimiter) {
        printf("[ELEMENT] %c\n", *temp);
        resources[j][k] = (int)*temp - '0';
      }
    }

    temp++;
  }
  return 0;
}
