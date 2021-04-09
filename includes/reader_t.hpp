#pragma once

#include "banker_t.hpp"
#include "customer_t.hpp"

#include <string>
#include <vector>

class reader_t {
  public:
    reader_t(std::string, std::vector<customer_t>*, banker_t*);
    reader_t();

    std::string get_path();
    size_t get_length();
    std::vector<std::string> get_content();

    std::vector<int> process_line(std::string);
    std::vector<std::string> read_contents(banker_t*, std::vector<customer_t>*);
    void print_contents();

  private:
    std::string path;
    std::vector<std::string> content;
    std::vector<std::vector<int>> resource_requests;
};

