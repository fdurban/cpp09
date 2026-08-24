#include "PmergeMe.hpp"
int main(int argc, char **argv)
{
  if(argc < 2)
    std::cout<<"Not enough numbers to compare...\n";
  PmergeMe sort;

  sort.sort(argc, argv);
}
