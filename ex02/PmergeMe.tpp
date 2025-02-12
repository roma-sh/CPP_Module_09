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


// Helper functions:

template <typename T>
T iterate_steps(T it, int steps)
{
	std::advance(it, steps);
	return it;
}

template <typename T>
bool _comp(T a, T b)
{
	return *a < *b;
}

unsigned long long get_jacobsthal_number(int n);


class PmergeMe
{
	std::vector<int> _v;
	std::deque<int> _q;

	public:
		PmergeMe();
		PmergeMe(PmergeMe const &original);
		PmergeMe &operator=(PmergeMe const &original);
		~PmergeMe();

		void fillVector(std::vector<std::string> &arguments);
		void fillDeque(std::vector<std::string> &arguments);
		void printVector();
		void printDeque();
		void sort_vec();
		void sort_deque();

template <typename T>
void _swap_pair(T it, int pair_level)
{
    T start = next(it, -pair_level + 1);
    T end = next(start, pair_level);
    while (start != end)
    {
        std::iter_swap(start, next(start, pair_level));
        start++;
    }
}

// 		template <typename T>
// 		void _merge_insertion_sort(T& container, int pair_level);
// };

template <typename T>
void _merge_insertion_sort(T& container, int pair_level)
{
	int	pair_available = container.size() / pair_level;
	if (pair_available < 2)
		return;
	std::cout << "pair_level: " << pair_level << std::endl;
	bool	odd_flag;
	int	shift = 2 * pair_level;
	if (pair_available % 2 == 1)
		odd_flag = true;
	else
		odd_flag = false;
	typename T::iterator start = container.begin();
	typename T::iterator last = iterate_steps(container.begin(), pair_level * pair_available);
	typename T::iterator end = iterate_steps(last, -(odd_flag * pair_level));
	for (typename T::iterator it = start; it != end; it = iterate_steps(it, shift))
	{
		typename T::iterator current_pair = iterate_steps(it, pair_level - 1);
		typename T::iterator next_pair = iterate_steps(it, pair_level * 2 - 1);
		if (*current_pair > *next_pair)
			_swap_pair(current_pair, pair_level);
	}
	_merge_insertion_sort(container, pair_level * 2);

	std::vector<typename T::iterator> main_container;
	std::vector<typename T::iterator> pend_container;

	main_container.insert(main_container.end(), iterate_steps(container.begin(), pair_level - 1));
	main_container.insert(main_container.end(), iterate_steps(container.begin(), pair_level * 2 - 1));

	for (int i = 4; i <= pair_available; i += 2)
	{
		pend_container.insert(pend_container.end(), iterate_steps(container.begin(), pair_level * (i - 1) - 1));
		main_container.insert(main_container.end(), iterate_steps(container.begin(), pair_level * i - 1));
	}

	int jacobsthal_number = get_jacobsthal_number(1);
	int insertedNum_Counter = 0;
	int offset = 0;
	for (int i = 2;; i++)
	{
		int current_jacobsthal = get_jacobsthal_number(i);
		int jacobsthal_diff = current_jacobsthal - jacobsthal_number;
		int nbr_of_times = jacobsthal_diff;
		if (jacobsthal_diff > static_cast<int>(pend_container.size()))
			break;
		typename std::vector<typename T::iterator>::iterator pend_it = iterate_steps(pend_container.begin(), jacobsthal_diff - 1);
		typename std::vector<typename T::iterator>::iterator bound_it = iterate_steps(main_container.begin(), current_jacobsthal + insertedNum_Counter);

		while (nbr_of_times)
		{
			typename std::vector<typename T::iterator>::iterator idx = std::upper_bound(main_container.begin(), bound_it, *pend_it, _comp<typename T::iterator>);
			typename std::vector<typename T::iterator>::iterator inserted = main_container.insert(idx, *pend_it);
			nbr_of_times--;
			pend_it = pend_container.erase(pend_it);
			pend_it = iterate_steps(pend_it, -1);
			offset += (inserted - main_container.begin()) == current_jacobsthal + insertedNum_Counter;
			bound_it = iterate_steps(main_container.begin(), current_jacobsthal + insertedNum_Counter - offset);
		}

		jacobsthal_number = current_jacobsthal;
		insertedNum_Counter += jacobsthal_diff;
		offset = 0;

	}

	for (size_t i = 0; i < pend_container.size(); i++)
	{
		typename std::vector<typename T::iterator>::iterator pend_it = iterate_steps(pend_container.begin(), i);
		typename std::vector<typename T::iterator>::iterator bound_it = iterate_steps(main_container.begin(), main_container.size() - pend_container.size() + i);
		typename std::vector<typename T::iterator>::iterator idx = std::upper_bound(main_container.begin(), bound_it, *pend_it, _comp<typename T::iterator>);
		main_container.insert(idx, *pend_it);
	}

	if (odd_flag)
	{
		typename T::iterator ood_pair = iterate_steps(end, pair_level - 1);
		typename std::vector<typename T::iterator>::iterator idx = std::upper_bound(main_container.begin(), main_container.end(), ood_pair, _comp<typename T::iterator>);
		main_container.insert(idx, ood_pair);
	}

	std::vector<int> temp;
	temp.reserve(container.size()); // reserve memory for the vector
	for (typename std::vector<typename T::iterator>::iterator it = main_container.begin(); it != main_container.end(); it++)
	{
		for (int i = 0; i < pair_level; i++)
		{
			typename T::iterator pair_start = *it;
			iterate_steps(pair_start, -pair_level + i + 1);
			temp.insert(temp.end(), *pair_start);
		}
	}

	typename T::iterator it = container.begin();
	typename std::vector<int>::iterator temp_it = temp.begin();
	while (temp_it != temp.end())
	{
		*it = *temp_it;
		it++;
		temp_it++;
	}
}
};


#endif
