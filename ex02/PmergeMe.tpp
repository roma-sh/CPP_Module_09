#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <deque>
#include <string>


class PmergeMe
{
	std::vector<int> _v;
	std::deque<int> _q;

	public:
		PmergeMe();
		PmergeMe(PmergeMe const &original);
		PmergeMe &operator=(PmergeMe const &original);
		~PmergeMe();

		void fillVector(int argc, char **argv);
		void fillDeque(int argc, char **argv);
		void printVector();
		void printDeque();
		void sortVector();
		void sortDeque();
};


#endif
