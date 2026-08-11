#include <iostream>
#include <deque>
#include <vector>
#include "PmergeMe.hpp"

PmergeMe::PmergeMe(): comparisonCountVector(0), comparisonCountDeque(0)
{}

PmergeMe::PMergeMe(const PmergeMe &other): comparisonCountVector(other.comparisonCountVector), comparisonCountDeque(other.comparisonCountDeque)
{
}

PmergeMe &PmergeMe::operator=(const PmergeMe &other)
{}
