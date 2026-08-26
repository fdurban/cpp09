#include "PmergeMe.hpp"
int main(int argc, char **argv)
{
  if(argc < 2)
  {
    std::cerr<<"Not enough numbers to compare...\n";
    return 1;
  }
  PmergeMe sort;
  sort.sort(argc, argv);
  return 0;
}
