class customer_t {
  public:
    customer_t(std::vector<int>, std::vector<int>, int);
    customer_t();

    int get_number();
    std::vector<int> get_maximum();
  
    void print_vector(std::vector<int>);
    void print();

  private:
    std::vector<int> initial_allocation;
    std::vector<int> maximum;
    std::vector<int> request;
    int number;
};

