#include <iostream>
#include <vector>
#include <sstream>

class PmergeMe
{
  private:
    struct Element
    {
      int value;
      size_t id;
      Element() : value(0), id(0) {}
      Element(int v, size_t i) : value(v), id(i) {}
      bool operator<(const Element& other) const {
        return this->value < other.value;
      }
    };
    size_t comparisonCountVector;
    size_t comparisonCountDeque;
    std::vector<Element> parseInput(int argc, char **argv);
    void  validateInput(const std::string &str);
    std::vector<size_t> generateJacobsthalSequence(size_t num_losers);
    std::vector<Element> sortWithIndex(std::vector<Element> &currentSeq);
    Element findLoserById(const std::vector< std::pair<size_t, Element> >& map, size_t winner_id);
  public:
    PmergeMe();
    PmergeMe &operator=(const PmergeMe &other);
    PmergeMe(const PmergeMe &other);
    ~PmergeMe();
    void  sort(int argc, char **argv);
};
