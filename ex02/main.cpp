#include "PmergeMe.tpp"

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		std::cerr << "Usage: " << argv[0] << " [Random positive numbers]" << std::endl;
		return 1;
	}
	PmergeMe pm;
	pm.fillVector(argc, argv);
	pm.fillDeque(argc, argv);
	pm.printVector();
	pm.printDeque();
	pm.sortVector();
	pm.sortDeque();
	pm.printVector();
	pm.printDeque();

	return 0;
}
