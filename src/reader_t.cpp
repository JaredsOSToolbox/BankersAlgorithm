#include "../includes/reader_t.hpp"
#include "../includes/customer_t.hpp"
#include "../includes/banker_t.hpp"

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>


reader_t::reader_t(std::string path, std::vector<customer_t>* clientel, banker_t* banker) {
  this->path = path;
  this->content = this->read_contents(banker, clientel);
}

reader_t::reader_t() {
  this->path = "";
  this->content = std::vector<std::string>();
}

std::string reader_t::get_path() { return this->path; }

std::vector<std::string> reader_t::get_content() { return this->content; }

size_t reader_t::get_length() { return this->content.size(); }

std::vector<int> reader_t::process_line(std::string line) {
  std::vector<int> values;
  // strtok for std::string

  std::istringstream iss(line);
  std::string token;
  while (std::getline(iss, token, ' ')) {
    // we are only interested in the first element, and avoids the
    // need to pre-process the string
    values.push_back(token[0] - '0'); // directly converts it from char to int repr of int
  }
  return values;
}

std::vector<std::string> reader_t::read_contents(banker_t* bank, std::vector<customer_t>* clientel) {
  std::vector<std::vector<int>> requests;

  std::ifstream file;
  file.open(this->path);
  std::vector<std::string> contents;

  if (!file.is_open()) {
    throw std::invalid_argument("cannot open file!");
  }

   int i = -1;

  for (std::string line; std::getline(file, line);) {
    if(i == -1){
      std::cout << "This is the total resources available" << std::endl;
    } else {
      std::cout << "adding customer " << i << "...." << std::endl;
    }

    requests.push_back(process_line(line));
    contents.push_back(line); // save a copy, this was from my compiler codebase
    ++i;
  }

  file.close();
  this->resource_requests = requests;
  return contents;
}

void reader_t::print_contents() {
  for (auto line : this->content) {
    std::cout << line << std::endl;
  }
}

