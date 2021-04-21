#include "../includes/banker_t.hpp"
#include "../includes/customer_t.hpp"
#include "../includes/reader_t.hpp"
#include "../includes/utils.hpp"

#include <stdio.h>

namespace Utils {
  
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

  void usage(void){
    printf("[INFO] usage: bankruptcy <input>\n");
  }


  std::set<std::filesystem::path> get_tests(std::string _path) {
    /*
     * Sort by filename
     * Source:
     * https://stackoverflow.com/questions/62409409/how-to-make-stdfilesystemdirectory-iterator-to-list-filenames-in-order
     */

    std::set<std::filesystem::path> container;

    for (const auto& entry : std::filesystem::directory_iterator(_path)) {
      container.insert(entry.path());
    }

    return container;
  }

  _C_
  bool all(Container& container) {
    /*
     * Equivalent to Python's all function
     * How to extend this to all containers in the STL
     * https://stackoverflow.com/questions/27359791/c-pass-any-container-to-function
    */
    for(auto element : container) {
      if (!element) {
        return false;
      }
    }
    return true;
  }

  _C_
  bool any_(Container& container) {
    int _count = 0;
    for(auto element : container) {
      if(element){ _count++; }
    }
    return (_count > 0);
  }

  void conduct_certain_test(bool verbose, std::string file_path, std::vector<bool>* success, int index) {
      const char* _path = file_path.c_str();
      printf("[INFO] Conducting test on %s\n", _path);
      banker_t banker = banker_t();

      reader_t source = reader_t(_path, &banker);
      std::cout << banker << std::endl; 
      bool _success = banker.conduct_simulation(verbose);
      (*success)[index] = _success;
  }

  void conduct_all(bool verbose) {

    std::vector<bool> iterations(TEST_COUNT, false); // we know how many tests there are

    std::set<std::filesystem::path> paths = get_tests("inputs/");

    int i = 0;

    for(auto& entry : paths) {
      conduct_certain_test(verbose, entry, &iterations, i++);
    }

    assert(all(iterations) == true);
    printf("[INFO] All %d assertions passed!\n", TEST_COUNT);
  }

  void customer_bank_test(void) {

    /*
     * Directly pulled from the example code
    */

    EVec::extended_vector_t<int> alloc({3, 1, 5});
    EVec::extended_vector_t<int> max({5, 2, 6});
    EVec::extended_vector_t<int> need = alloc - max;
    EVec::extended_vector_t<int> request({3, 3, 3});

    EVec::extended_vector_t<int> available_resources = alloc + max + need;

    customer_t* c0 = new customer_t(alloc, request, 0);
    customer_t* c1 = new customer_t(max, max, 1);
    customer_t* c2 = new customer_t(alloc, (alloc + available_resources), 2);

    std::vector<customer_t*> customers({c0, c1, c2});

    banker_t bank = banker_t(available_resources, customers);

    std::cout << "Bank: " << std::endl << bank << std::endl;

    c0->generate_request();
    auto _request = c0->request();

    std::cout << "random request: ";
    print_vector(c0->request().get_data());
    std::cout << std::endl;
    printf("Is this request available %s\n", (bank.is_available(_request)) ? "yes" : "no");

    for (auto element : customers) {
      free(element);
    }
  }
}

