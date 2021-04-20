#pragma once

#include <iostream>
#include <vector>
#include <filesystem>
#include <string>
#include <set>
#include <assert.h>

namespace Utils {

  #define _T_ template <typename T>
  #define _C_ template <class Container>
  #define TEST_COUNT 4
  #define PEDANTIC true

  #define MUTEX_SAFE(x) pthread_mutex_lock(&mutex_); \
                      x; \
                      pthread_mutex_unlock(&mutex_);
  #define DEADLOCK 500

  void usage(void);
  void version(void);

  std::set<std::filesystem::path> get_tests(std::string);
  _C_
  bool all(Container&); 
  _C_
  bool any_(Container&);

  void conduct_all(bool);

  void conduct_certain_test(bool, std::string, std::vector<bool>*, int);
}

