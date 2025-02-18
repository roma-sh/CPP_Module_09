#ifndef PMERGEME_TPP
#define PMERGEME_TPP

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

unsigned long long get_jacobsthal_number(int n);

template <typename T>
void copy_sorted_numbers(const std::vector<typename T::iterator>& main_container, T& container, int pair_level)
{
	// since main_container is a vector of iterators relative to the container we can't just copy it to the container
	// temp vector to store the sorted numbers and then copy them to the container
	std::vector<int> temp;
	temp.reserve(container.size()); // Optimize memory allocation

	// reserve memory for the vector because
	// temp starts empty, so every time temp.insert(..) runs, the vector may dynamically grow, causing multiple reallocations.
	// and temp grows dynamically, inserting new elements may require copying existing elements to a larger memory block.
	//which will be slow.
	for (typename std::vector<typename T::iterator>::const_iterator it = main_container.begin(); it != main_container.end(); ++it)
	{
		typename T::iterator pair_start = *it; // Dereference to get actual iterator
		for (int i = 0; i < pair_level; i++)
		{
			typename T::iterator current = iterate_steps(pair_start, -pair_level + i + 1); // Correct iteration
			temp.push_back(*current); // Store value in temp
		}
	}
	// Copy the sorted numbers from temp to container
	typename T::iterator container_it = container.begin();
	for (int value : temp)
	{
		*container_it = value;
		++container_it;
	}
}

template <typename T>
void insert_odd_pair(std::vector<typename T::iterator>& main_container, typename T::iterator end, int pair_level)
{
	typename T::iterator ood_pair = iterate_steps(end, pair_level - 1);
	typename std::vector<typename T::iterator>::iterator idx = std::upper_bound(main_container.begin(), main_container.end(), ood_pair, _comp<typename T::iterator>);
	main_container.insert(idx, ood_pair);
}

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
		void _merge_insertion_sort(T& container, int pair_level)
		{
			int	pair_available = container.size() / pair_level;
			if (pair_available < 2)
				return;
			bool	odd_flag;
			int	shift = 2 * pair_level;
			if (pair_available % 2 == 1)
				odd_flag = true;
			else
				odd_flag = false;
			typename T::iterator start = container.begin();
			typename T::iterator last = iterate_steps(container.begin(), pair_level * pair_available);
			typename T::iterator end = iterate_steps(last, -(odd_flag * pair_level)); // we will stop at the last pair if there is an odd number of pairs
			// swap pairs:
			for (typename T::iterator it = start; it != end; it = iterate_steps(it, shift))
			{
				typename T::iterator current_pair = iterate_steps(it, pair_level - 1);
				typename T::iterator next_pair = iterate_steps(it, pair_level * 2 - 1);
				if (*current_pair > *next_pair)
					_swap_pair(current_pair, pair_level);
			}
			_merge_insertion_sort(container, pair_level * 2);
			// vector of iterators not the actual valuse:
			// Sorting and inserting iterators is lightweight compared to shifting
			//entire values if we want to insert a value in the middle of the container
			// that will Saves memory and speeds up sorting.
			std::vector<typename T::iterator> main_container;
			std::vector<typename T::iterator> pend_container;
			// insert the first two pairs b1 a1
			main_container.insert(main_container.end(), iterate_steps(container.begin(), pair_level - 1));
			main_container.insert(main_container.end(), iterate_steps(container.begin(), pair_level * 2 - 1));
			// insert all the a numbers in main, insert all the b numbers in pend
			for (int i = 4; i <= pair_available; i += 2)
			{
				main_container.insert(main_container.end(), iterate_steps(container.begin(), pair_level * i - 1));
				pend_container.insert(pend_container.end(), iterate_steps(container.begin(), pair_level * (i - 1) - 1));
			}
			// when we want to insert a number in main, we will not search in the whole container,
			// we will search until the last number we inserted + the jacobsthal number
			int jacobsthal_number = get_jacobsthal_number(1);
			int insertedNum_Counter = 0;
			int offset = 0;
			// insert the numbers in the main container
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
				// update the jacobsthal number and the inserted number counter
				jacobsthal_number = current_jacobsthal;
				insertedNum_Counter += jacobsthal_diff;
				offset = 0;

			}
			// insert the remaining numbers in the main container
			for (size_t i = 0; i < pend_container.size(); i++)
			{
				typename std::vector<typename T::iterator>::iterator pend_it = iterate_steps(pend_container.begin(), i);
				typename std::vector<typename T::iterator>::iterator bound_it = iterate_steps(main_container.begin(), main_container.size() - pend_container.size() + i);
				typename std::vector<typename T::iterator>::iterator idx = std::upper_bound(main_container.begin(), bound_it, *pend_it, _comp<typename T::iterator>);
				main_container.insert(idx, *pend_it);
			}
			// if there is an odd number of pairs, we will insert the last pair
			if (odd_flag)
				insert_odd_pair<T>(main_container, end, pair_level); // <T> is used to specify the type of the container so that the compiler can deduce the type of the iterator
			// copy the sorted numbers from the main_container to the actual container
			copy_sorted_numbers(main_container, container, pair_level);
		}
};

#endif
