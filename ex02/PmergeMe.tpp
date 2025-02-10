#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <deque>
#include <string>
#include <sstream>
#include <regex>


class PmergeMe
{
	std::vector<int> _v;
	std::deque<int> _q;

	public:
		PmergeMe() {};
		PmergeMe(PmergeMe const &original)
		{
			_v = original._v;
			_q = original._q;
		}

		PmergeMe &operator=(PmergeMe const &original)
		{
			if (this != &original)
			{
				_v = original._v;
				_q = original._q;
			}
			return *this;
		}
		~PmergeMe() {};

		void fillVector(std::vector<std::string> &arguments)
		{
			for (std::vector<std::string>::iterator it = arguments.begin(); it != arguments.end(); it++)
			{
				_v.push_back(std::stoi(*it));
			}
		}
		void fillDeque(std::vector<std::string> &arguments)
		{
			for (std::vector<std::string>::iterator it = arguments.begin(); it != arguments.end(); it++)
			{
				_q.push_back(std::stoi(*it));
			}
		}
		void printVector()
		{
			std::copy(_v.begin(), _v.end(), std::ostream_iterator<int>(std::cout, " "));
			std::cout << std::endl;
		}
		void printDeque()
		{
			std::copy(_q.begin(), _q.end(), std::ostream_iterator<int>(std::cout, " "));
			std::cout << std::endl;
		}
};




#endif
