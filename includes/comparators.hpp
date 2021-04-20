#define _T template <typename T>

namespace Comparator {
  class Comparator {
    public:
      explicit Comparator();
      virtual bool compare(void*);
  };

  _T
  class has_negative : public Comparator<T> {
    public:
      has_negative();
      bool compare(void* a);
  };


  _T
  class is_positive : public Comparator<T> {
    public:
      is_positive();
      bool compare(void* a);
  };
}


