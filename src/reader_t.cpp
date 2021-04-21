#include "../includes/reader_t.hpp"
#include "../includes/customer_t.hpp"
#include "../includes/banker_t.hpp"

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>

#define SPACES 3

reader_t::reader_t(std::string path, banker_t* banker) {
//reader_t::reader_t(std::string path, std::vector<customer_t*>* clientel) {
  this->path = path;
  this->content = this->read_contents(banker);
  //this->content = this->read_contents(clientel);
}

reader_t::reader_t() {
  this->path = "";
  this->content = std::vector<std::string>();
}

std::string reader_t::get_path() { return this->path; }

std::vector<std::string> reader_t::get_content() { return this->content; }

size_t reader_t::get_length() { return this->content.size(); }

//std::vector<std::vector<int>> reader_t::process_line(std::string line) {
std::vector<EVec::extended_vector_t<int>> reader_t::process_line(std::string line) {
  /*
   * FIXME : allocated and requested have not been properly parsed yet
   * Please fix this because I am now really tired and I want to go to bed right now
   * How much more can I type without looking directly at the keyboard and my computer screen?
   * Quite alot actually, good shit jared
  */
  const char delimiter = ',';

  std::vector<EVec::extended_vector_t<int>> resources;
  //std::vector<std::vector<int>> resources;

  const char* temp = line.c_str();
  int i = 0;  // how many spaces we have encountered during the parsing phase
  //std::vector<int> p;
  EVec::extended_vector_t<int> p;

  while (*temp != '\0') {
    if (i == SPACES) {
      // stop counting and refresh
      i = 0;
      resources.push_back(p);
      p.clear();
    }

    if (isspace(*temp)) {
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

  resources.push_back(p);

  return resources;
}


std::vector<std::string> reader_t::read_contents(banker_t* banker) {
  std::vector<EVec::extended_vector_t<int>> requests;
  std::vector<customer_t*> clientel;

  std::ifstream file;
  file.open(this->path);
  std::vector<std::string> contents;

  if (!file.is_open()) {
    throw std::invalid_argument("cannot open file!");
  }

   int i = -1;

  for (std::string line; std::getline(file, line);) {
    if(line.size() == 0){
      continue;
    }

    auto processed = process_line(line);

    if(i == -1){
      // UPDATE FUNDS
      banker->update_avaialble_funds(processed[0]);
    } else {
      std::cout << "adding customer " << i << "...." << std::endl;
      // 0 : allocated
      // 1 : request
      // CREATE CUSTOMER
      customer_t* customer = new customer_t(processed[0], processed[1], i);
      clientel.push_back(customer);
    }

    contents.push_back(line); // save a copy, this was from my compiler codebase
    ++i;
  }

  file.close();
  this->resource_requests = requests;
  banker->add_customers(clientel);
  return contents;
}

void reader_t::print_contents() {
  for (auto line : this->content) {
    std::cout << line << std::endl;
  }
}

