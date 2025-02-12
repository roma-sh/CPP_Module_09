#include "PmergeMe.tpp"

PmergeMe::PmergeMe() {};
PmergeMe::PmergeMe(PmergeMe const &original)
{
	_v = original._v;
	_q = original._q;
}

PmergeMe &PmergeMe::operator=(PmergeMe const &original)
{
	if (this != &original)
	{
		_v = original._v;
		_q = original._q;
	}
	return *this;
}
PmergeMe::~PmergeMe() {};

void PmergeMe::fillVector(std::vector<std::string> &arguments)
{
	for (std::vector<std::string>::iterator it = arguments.begin(); it != arguments.end(); it++)
	{
		_v.push_back(std::stoi(*it));
	}
}
void PmergeMe::fillDeque(std::vector<std::string> &arguments)
{
	for (std::vector<std::string>::iterator it = arguments.begin(); it != arguments.end(); it++)
	{
		_q.push_back(std::stoi(*it));
	}
}
void PmergeMe::printVector()
{
	std::copy(_v.begin(), _v.end(), std::ostream_iterator<int>(std::cout, " "));
	std::cout << std::endl;
}
void PmergeMe::printDeque()
{
	std::copy(_q.begin(), _q.end(), std::ostream_iterator<int>(std::cout, " "));
	std::cout << std::endl;
}

void PmergeMe::sort_vec()
{
	_merge_insertion_sort(_v, 1);
}

void PmergeMe::sort_deque()
{
	_merge_insertion_sort(_q, 1);
}


unsigned long long get_jacobsthal_number(int n)
{
	if (n == 0) return 0;
	if (n == 1) return 1;
	return get_jacobsthal_number(n - 1) + 2 * get_jacobsthal_number(n - 2);
}
