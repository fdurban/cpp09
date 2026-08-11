#include <isotream>

class PmergeMe
{
  private:
    size_t comparisonCountVector;
    size_t comparisonCountDeque;
    
  public:
    PmergeMe();
    PmergeMe &operator(const PmergeMe &other);
    PmergeMe(const PmergeMe &other);
    ~PmergeMe();
    sort(int argc, char **argv);
}
